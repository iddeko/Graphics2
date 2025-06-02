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
#include <optional>

class Mover {
public:
	cyclone::RigidBody* body;
	cyclone::Vector3 halfSize;

	Mover() {
		this->body = new cyclone::RigidBody();
		this->setState(cyclone::Vector3{ 0., 1., 0. }, cyclone::Quaternion(), cyclone::Vector3{ 1., 0.5, 0.5 }, cyclone::Vector3{ 0., 0, 0. });
	};
	~Mover() {};
	void setState(const cyclone::Vector3 &position, const cyclone::Quaternion &orientation,
		const cyclone::Vector3 &extents, const cyclone::Vector3 &velocity) {
		this->body->setPosition(position);
		this->body->setOrientation(orientation);
		this->body->setVelocity(velocity);
		this->body->setRotation(cyclone::Vector3(0, 0, 0));
		this->halfSize = extents; //size info
		cyclone::real mass = this->halfSize.x * this->halfSize.y * this->halfSize.z * 2.0f; //automatically set the mass
		this->body->setMass(mass);
		cyclone::Matrix3 tensor;
		tensor.setBlockInertiaTensor(this->halfSize, mass); //Inertia tensor matrix
		this->body->setInertiaTensor(tensor);
		this->body->setLinearDamping(0.9f); //Set the damping for linear and angular motion
		this->body->setAngularDamping(0.8f);
		this->body->clearAccumulators();
		this->body->setAcceleration(0, -10.0f, 0); //Set the gravity
		this->body->setAwake();
		this->body->setCanSleep(true);
		//Calculate the transformation matrix and convert to world inertia tensor matrix
		this->body->calculateDerivedData();
	}
	
	/*
	void setConnection(Mover &a) {
		this->spring = new cyclone::MySpring(a.particle, (double)20, (double)5);
		forces->add(this->particle, this->spring);
	}

	void setAnchorConnection(cyclone::Vector3* anchor, double springConstant, double restLength) {
		this->anchor_spring = new cyclone::MyAnchoredSpring(anchor, springConstant, restLength);
		forces->add(this->particle, this->anchor_spring);
	}
	*/

	void stop() {}

	void Mover::update(float duration) {
		if (body) {
			this->body->integrate(duration);
			this->body->calculateDerivedData(); //re-calculate the transformation matrix
		}
	}

	void draw(int shadow, int name) {
		GLfloat mat[16];
		body->getGLTransform(mat);

		if (shadow == 1) {
			glColor3f(0.1f, 0.1f, 0.1f);
		}
		else {
			glColor3f(1.f, 0.1f, 0.1f);
		}

		glPushMatrix();
		glMultMatrixf(mat);
		glScalef(this->halfSize.x * 2, this->halfSize.y * 2, this->halfSize.z * 2);
		glutSolidCube(1.0f);
		glPopMatrix();

		if (shadow != 1) {
			glColor3f(1, 0, 0); //Line color
			glLineWidth(3.0f); //Line Width
			glPushMatrix();
			glMultMatrixf(mat);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0); //Starting point
			glVertex3f(0, 0 + 3, 0); //Ending point
			glEnd();
			glPopMatrix();

			glColor3f(0, 1, 0); //Line color
			glLineWidth(3.0f); //Line Width
			glPushMatrix();
			glMultMatrixf(mat);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0); //Starting point
			glVertex3f(0 + 3, 0, 0); //Ending point
			glMultMatrixf(mat);
			glEnd();
			glPopMatrix();

			glColor3f(0, 0, 1); //Line color
			glLineWidth(3.0f); //Line Width
			glPushMatrix();
			glMultMatrixf(mat);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0); //Starting point
			glVertex3f(0, 0, 0 + 3); //Ending point
			glMultMatrixf(mat);
			glEnd();
			glPopMatrix();
		}
	}
};