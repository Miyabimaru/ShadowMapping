


#include <iostream>
#include <windows.h>


#include <gl/glew.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <Fl/Fl_Gl_Window.H>

#include "MyGlWindow.h"

int main()
{
	Fl::scheme("plastic");// plastic
	int width = 800;
	int height = 800;
	Fl_Double_Window* wind = new Fl_Double_Window(100, 100, width, height, "GL 3D FrameWork");

	wind->begin();		// put widgets inside of the window
	MyGlWindow* gl = new MyGlWindow(10, 10, width - 20, height - 50);

	wind->resizable(gl);
	wind->show();	// this actually opens the window


	Fl::run();
	delete wind;

	return 1;

}
