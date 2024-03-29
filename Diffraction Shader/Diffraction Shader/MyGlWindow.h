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
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Choice.H>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "Viewer.h"
#include "ModelView.h"
#include "CheckeredFloor.h"
#include "ModelLoader.h"

#include "Sphere.h"

#include "IDrawable.h"
#include "material.h"
#include "LightManager.h"
#include "ILight.h"
#include "ShadowMap.h"

#pragma warning(pop)


class MyGlWindow : public Fl_Gl_Window {
public:
	MyGlWindow(int x, int y, int w, int h);
	~MyGlWindow();

	Fl_Browser *browser;
	Fl_Choice *choiceSimpleObjectSpawner;
	std::string currentSimpleObjectName;
	std::vector<IDrawable *> _objectList;
	std::vector<ILight *> _lightList;

	IDrawable * _selectedObject;

	//Callbacks
	void loadModel();
	void deleteModel();
	void changePosition();
	void changeMaterial();

	void spawnSimpleObject();
	void updateSelected(IDrawable * drawable);

private:
	void draw();
	int handle(int);	
	void initialize();
	int first;

	LightManager * _lightManager;
	ShadowMap * _shadowMap;

	Viewer *m_viewer;
	Model m_model;

	// Position editor
	Fl_Float_Input * posx;
	Fl_Float_Input * posy;
	Fl_Float_Input * posz;

	// Material editor
		// Ka
	Fl_Float_Input * matkax;
	Fl_Float_Input * matkay;
	Fl_Float_Input * matkaz;
		// Kd
	Fl_Float_Input * matkdx;
	Fl_Float_Input * matkdy;
	Fl_Float_Input * matkdz;
		// Ks
	Fl_Float_Input * matksx;
	Fl_Float_Input * matksy;
	Fl_Float_Input * matksz;
};
