
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
#include "3DUtils.h"
#include "Object.h"
#include "Spring.h"

#include "Viewer.h"
#include <vector>

#include "core.h"
#include <FL/Fl_Light_Button.H>
#include <pfgen.h>
#include <Plane.h>

#include "Firework.h"


class MyGlWindow : public Fl_Gl_Window {
public:
	MyGlWindow(int x, int y, int w, int h);


	Fl_Slider* time;
	Fl_Light_Button* ui;
	int run;
	void update();
	void doPick();
	void step();
	void test();
	int selected;

private:
	void draw();					// standard FlTk

	//3D position when mouse is pushing
	cyclone::Vector3 pickingStartPos;
	clock_t pickingStartTime;

	cyclone::Vector3 anchorPos;
	std::optional<Plane> plane;
	std::vector<Firework> fireworks;
	
	int handle(int);				// standard FlTk

	float fieldOfView;
	Viewer *m_viewer;
	std::vector<Mover> movers;

	void setProjection(int clearProjection = 1);
	void getMouseNDC(float& x, float& y);
	void setupLight(float x, float y, float z);
	void putText(char* string, int x, int y, float r, float g, float b);
};
