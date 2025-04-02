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
#include "3DUtils.h"

#include "Viewer.h"
#include <vector>

#include <iostream>

#include "core.h"

class Mover {
public:
	cyclone::Particle particle;

	float size = 2;
	Mover() {
		particle.setPosition(0., 20., 0.);
		
		particle.setMass(2.0f); // 2.0kg
		particle.setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
		particle.setAcceleration(0.0f, -1.0f, 0.0f);
		particle.setDamping(0.99f);

		//particle.setVelocity(0., 0., 0.);
		//particle.setMass(1.);
		//particle.setDamping(0.99);
		//particle.setAcceleration(cyclone::Vector3::GRAVITY);
	};
	~Mover() {};
	
	void stop(){}
	void update(float duration) {
		//particle.addForce(cyclone::Vector3(1., 0., 0.));
		particle.integrate(duration);

		cyclone::Vector3 pos = particle.getPosition();
		cyclone::Vector3 vel = particle.getVelocity();
		if (pos.y <= 0 + size) {
			pos.y = size;
			vel.y = -vel.y;
		}
		if (pos.x + size >= 100) {
			pos.x = 100 - size;
			vel.x = -vel.x;
		}
		particle.setPosition(pos);
		particle.setVelocity(vel);
	}

	void draw(int shadow, int name) {
		cyclone::Vector3 position = particle.getPosition();

		if (shadow == 1) {
			glLoadName(0);
			glColor3f(0.1f, 0.1f, 0.1f);
		} else {
			glLoadName(name);
			glColor3f(1.f, 0.1f, 0.1f);
		}
		glTranslated(position.x, position.y, position.z);
		glutSolidSphere(size, 30, 30);
		glLoadName(0);
	}
};