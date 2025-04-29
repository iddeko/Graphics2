#pragma once

#define NOMINMAX

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Fl/Fl_Double_Window.h>

#include "stdio.h"
#include "math.h"
#include "cyclone.h"
#include "pfgen.h"
#include "3DUtils.h"
#include "Spring.h"

#include "Viewer.h"
#include <vector>

#include <iostream>
#include "Plane.h"

#include "core.h"

class Mover {
public:
	cyclone::Particle *particle;
	cyclone::ParticleForceRegistry *forces;
	cyclone::ParticleGravity *gravity;
	cyclone::ParticleDrag *drag;
	cyclone::MySpring* spring = NULL;
	cyclone::MyAnchoredSpring* anchor_spring = NULL;

	float size = 2;
	Mover() {
		particle = new cyclone::Particle();
		particle->setPosition(3., 19., 0.);
		
		particle->setMass(1.0f);
		particle->setVelocity(0.0f, 0.0f, 0.0f); // 35m/s
		particle->setAcceleration(0.0f, 0.0f, 0.0f);

		gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -10, 0));
		drag = new cyclone::ParticleDrag(0.1, 0.01);
		forces = new cyclone::ParticleForceRegistry();
		forces->add(particle, gravity);
		forces->add(particle, drag);

		//particle->setVelocity(0., 0., 0.);
		particle->setMass(1.);
		particle->setDamping(1.);
		//particle->setAcceleration(cyclone::Vector3::GRAVITY);
	};
	~Mover() {};
	
	void setConnection(Mover &a) {
		this->spring = new cyclone::MySpring(a.particle, (double)20, (double)3);
		forces->add(this->particle, this->spring);
	}

	void setAnchorConnection(cyclone::Vector3* anchor, double springConstant, double restLength) {
		this->anchor_spring = new cyclone::MyAnchoredSpring(anchor, springConstant, restLength);
		forces->add(this->particle, this->anchor_spring);
	}

	void stop(){}
	void update(float duration, Plane &plane) {
		//particle->addForce(cyclone::Vector3(1., 0., 0.));
		forces->updateForces(duration);
		particle->integrate(duration);
	 	checkEdges();

		double distance = plane.getDistance(particle->getPosition(), size);
		if (abs(distance) < size && plane.inBounds(particle->getPosition())) {
			auto normal = plane.getNormal();
			if (distance < 0) {
				normal *= -1;
			}
			particle->setPosition(particle->getPosition() + (size - abs(distance)) * normal);
			particle->setVelocity(particle->getVelocity() - (2 * particle->getVelocity().dot(normal) * normal));
		}
	}

	void checkEdges() {
		cyclone::Vector3 pos = particle->getPosition();
		cyclone::Vector3 vel = particle->getVelocity();
		if (pos.y <= 0 + size) {
			pos.y = size;
			vel.y = -vel.y;
		}
		if (pos.x + size >= 100) {
			pos.x = 100 - size;
			vel.x = -vel.x;
		}
		if (pos.x <= -100 + size) {
			pos.x = -100 + size;
			vel.x = -vel.x;
		}
		if (pos.z + size >= 100) {
			pos.z = 100 - size;
			vel.z = -vel.z;
		}
		if (pos.z <= -100 + size) {
			pos.z = -100 + size;
			vel.z = -vel.z;
		}
		particle->setPosition(pos);
		particle->setVelocity(vel);
	}

	void draw(int shadow, int name) {
		cyclone::Vector3 position = particle->getPosition();

		if (shadow == 1) {
			glColor3f(0.1f, 0.1f, 0.1f);
		} else {
			glColor3f(1.f, 0.1f, 0.1f);
		}
		glPushMatrix();
		glTranslated(position.x, position.y, position.z);
		glutSolidSphere(size, 30, 30);
		glPopMatrix();
	}
};