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
#include <cyclone.h>
#include "3DUtils.h"

#include "Viewer.h"
#include <vector>

#include <iostream>

#include "core.h"

class Mover {
public:
	cyclone::Vector3 position = { 0., 3., 0. };
	float size = 2;
	Mover() {};
	~Mover() {};

	void draw(int shadow) {
		if (shadow == 1) {
			glColor3f(0.1f, 0.1f, 0.1f);
		} else {
			glColor3f(1.f, 0.1f, 0.1f);
		}
		glTranslated(position.x, position.y, position.z);
		glutSolidSphere(size, 30, 30);
	}
};