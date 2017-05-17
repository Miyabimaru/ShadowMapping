//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma warning(push)
#pragma warning(disable:4311)		// convert void* to long
#pragma warning(disable:4312)		// convert long to void*


#include <windows.h>
#include <iostream>

#include "GL/glew.h"
#include <GL/gl.h>
#include <string>
#include <stack>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <FL/Fl_Widget.H>
#include <FL/Fl_File_Chooser.H>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "Viewer.h"
#include "ModelView.h"
#include "CheckeredFloor.h"

#pragma warning(pop)


class MyGlWindow : public Fl_Gl_Window {
public:
	void loadModel();
	MyGlWindow(int x, int y, int w, int h);
	~MyGlWindow();

	Fl_Input *input;

private:
	void draw();
	int handle(int);	
	void initialize();
	int first;

	Viewer *m_viewer;
	checkeredFloor * m_floor;
	Model m_model;
};
