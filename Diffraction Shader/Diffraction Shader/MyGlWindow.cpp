#include "MyGlWindow.h"
#include "debug.h"

static double DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static double DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static double DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

static void AddModelCallback(Fl_Widget *w, void *f) {
	((MyGlWindow *)f)->callback();
	((MyGlWindow *)f)->loadModel();
}

static void DeleteModelCallback(Fl_Widget *w, void *f) {
	((MyGlWindow *)f)->callback();
	((MyGlWindow *)f)->deleteModel();
}

void MyGlWindow::deleteModel()
{
	int index = browser->value();
	if (index > 0)
	{
		modelList.erase(modelList.begin() + index - 1);
		browser->remove(index);
		this->initialize();
		this->redraw();
	}
}

void MyGlWindow::loadModel()
{
	char *pathFile = fl_file_chooser("Select a file", "*.obj", 0);
	std::string path = std::string(pathFile);
	std::string fileName = path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - path.find_last_of('/') - 1);
	const char *c_fileName = fileName.c_str();
	browser->add(c_fileName);
	ModelLoader *m_3DModel = new ModelLoader(pathFile, c_fileName);
	modelList.push_back(m_3DModel);
	this->initialize();
	this->redraw();
}

MyGlWindow::MyGlWindow(int x, int y, int w, int h)
: Fl_Gl_Window(x, y, w, h)
//==========================================================================
{	
	browser = new Fl_Browser(w + 20, 50, 250, h/2);
	browser->type(FL_HOLD_BROWSER);

	Fl_Button *buttonAddModel = new Fl_Button(w + 20, 10, 115, 30, "Load a model");
	buttonAddModel->callback(AddModelCallback, (void *)this);

	Fl_Button *buttonDeleteModel = new Fl_Button(w + 140, 10, 125, 30, "Delete a model");
	buttonDeleteModel->callback(DeleteModelCallback, (void *)this);

	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);
	first = 0;
	m_floor = 0;
	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);
}

void MyGlWindow::draw(void)
{
	glClearColor(0.2f, 0.2f, .2f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);

	
	if (!first) {
		glewExperimental = TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			//Problem: glewInit failed, something is seriously wrong.
			std::cout << "glewInit failed, aborting." << std::endl;
		}

		first = 1;
		glEnable(GL_DEBUG_OUTPUT);
		initialize();
		glDebugMessageCallback(Core::DebugOutput::myCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
			GL_DONT_CARE, 0, NULL, GL_TRUE);
	}
	
	
	glViewport(0, 0, w(), h());


	glm::vec3 eye = m_viewer->getViewPoint(); // m_viewer->getViewPoint().x(), m_viewer->getViewPoint().y(), m_viewer->getViewPoint().z());
	glm::vec3 look = m_viewer->getViewCenter();   //(m_viewer->getViewCenter().x(), m_viewer->getViewCenter().y(), m_viewer->getViewCenter().z());
	glm::vec3 up = m_viewer->getUpVector(); // m_viewer->getUpVector().x(), m_viewer->getUpVector().y(), m_viewer->getUpVector().z());

	glm::mat4 view = glm::lookAt(eye, look, up);

	glm::mat4 projection = glm::perspective(45.0f, 1.0f*w() / h(), 0.1f, 500.0f);

	if (m_floor)
		m_floor->draw(m_model.getMatrix(), view, projection);

	m_model.glPushMatrix();
	m_model.glTranslate(0, 1, 0);

	if (_sphere1)
		_sphere1->Draw(m_model.getMatrix(), view, projection);

	if (modelList.size() > 0)
	{
		for each (ModelLoader *model in modelList)
		{
			m_model.glTranslate(2, 0, 0);
			model->draw(m_model.getMatrix(), view, projection);
		}
	}

	m_model.glPopMatrix();
}

MyGlWindow::~MyGlWindow()
{
	if (_lightManager)
		delete _lightManager;
	if (m_floor)
		delete m_floor;
	if (_sphere1)
		delete _sphere1;
}

#include "PhongShader.h"

void MyGlWindow::initialize()
{
	_lightManager = new LightManager();
	_lightManager->addPointLight(
		glm::vec4(50, 50, 50, 1),
		glm::vec3(1, 1, 1),
		glm::vec3(1, 1, 1),
		glm::vec3(1, 1, 1)
	);

	_lightManager->addPointLight(
		glm::vec4(0, 50, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0)
	);

	_sphere1 = new Sphere(1.0, 60, 60, new PhongShader(), _lightManager, "simple_phong.vert", "simple_phong.frag");
	m_floor = new checkeredFloor();
}



int m_pressedMouseButton;
int m_lastMouseX;
int m_lastMouseY;

int MyGlWindow::handle(int e)
//==========================================================================
{
	switch (e) {
	case FL_SHOW:		// you must handle this, or not be seen!
		show();
		return 1;
	case FL_PUSH:
	{

					m_pressedMouseButton = Fl::event_button();

					//	  m_viewer->setAspectRatio( static_cast<double>(this->w()) / static_cast<double>(this->h()) );

					m_lastMouseX = Fl::event_x();
					m_lastMouseY = Fl::event_y();
	}
		damage(1);
		return 1;
	case FL_RELEASE:
		m_pressedMouseButton = -1;
		damage(1);
		return 1;
	case FL_DRAG: // if the user drags the mouse
	{

					  double fractionChangeX = static_cast<double>(Fl::event_x() - m_lastMouseX) / static_cast<double>(this->w());
					  double fractionChangeY = static_cast<double>(m_lastMouseY - Fl::event_y()) / static_cast<double>(this->h());

					  if (m_pressedMouseButton == 1) {
						  m_viewer->rotate(fractionChangeX, fractionChangeY);
					  }
					  else if (m_pressedMouseButton == 2) {
						  m_viewer->zoom(fractionChangeY);
					  }
					  else if (m_pressedMouseButton == 3) {
						  m_viewer->translate(-fractionChangeX, -fractionChangeY, (Fl::event_key(FL_Shift_L) == 0) || (Fl::event_key(FL_Shift_R) == 0));
					  }
					  else {
						  std::cout << "Warning: dragging with unknown mouse button!  Nothing will be done" << std::endl;
					  }

					  m_lastMouseX = Fl::event_x();
					  m_lastMouseY = Fl::event_y();
					  redraw();
	}

		return 1;

	case FL_KEYBOARD:
		return 0;

	default:
		return 0;
	}
}

