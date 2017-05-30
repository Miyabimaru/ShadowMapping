#include "MyGlWindow.h"
#include "debug.h"

static double DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static double DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static double DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

static void changeSimpleObjectSelection(Fl_Widget *w, void *f) {
	((MyGlWindow *)f)->callback();

	Fl_Choice * choice = (Fl_Choice *)w;
	MyGlWindow * win = (MyGlWindow *)f;

	win->currentSimpleObjectName = choice->menu()[choice->value()].label();

	std::cout << "current object selected: " << win->currentSimpleObjectName << std::endl;
}

static void AddSimpleObjectCallback(Fl_Widget *w, void *f) {
	((MyGlWindow *)f)->callback();
	((MyGlWindow *)f)->spawnSimpleObject();
}

static void AddModelCallback(Fl_Widget *w, void *f) {
	((MyGlWindow *)f)->callback();
	((MyGlWindow *)f)->loadModel();
}

static void DeleteModelCallback(Fl_Widget *w, void *f) {
	((MyGlWindow *)f)->callback();
	((MyGlWindow *)f)->deleteModel();
}

static void ChangePositionCallback(Fl_Widget *w, void *f) {
	Fl_Float_Input * widget = (Fl_Float_Input *)w;
	std::cout << "POSITION VALUE: " << widget->value() << std::endl;
	((MyGlWindow *)f)->callback();
	((MyGlWindow *)f)->changePosition();
}

static void ChangeMaterialCallback(Fl_Widget *w, void *f) {
	Fl_Float_Input * widget = (Fl_Float_Input *)w;
	std::cout << "MAT VALUE: " << widget->value() << std::endl;
	((MyGlWindow *)f)->callback();
	((MyGlWindow *)f)->changeMaterial();
}

static void ChangeSelectionCallback(Fl_Widget *w, void *f) {
	Fl_Browser * br = (Fl_Browser *)w;
	MyGlWindow * win = (MyGlWindow *)f;
	int index = br->value();
	std::cout << "CALLBACK BR " << index << std::endl;
	if (index > 0)
		win->updateSelected(win->_objectList[index - 1]);
	else
		win->updateSelected(nullptr);
}

void MyGlWindow::deleteModel()
{
	int index = browser->value();
	if (index > 0)
	{
		_objectList.erase(_objectList.begin() + index - 1);
		browser->remove(index);
		this->updateSelected(nullptr);
		//this->initialize();
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
	_objectList.push_back(m_3DModel);
	//this->initialize();
	this->redraw();
}

void MyGlWindow::changePosition()
{
	if (_selectedObject != nullptr)
	{
		_selectedObject->setPosition(
			glm::vec3(atof(posx->value()), atof(posy->value()), atof(posz->value()))
		);

		this->redraw();
	}
	else
		updateSelected(_selectedObject);
}

void MyGlWindow::changeMaterial()
{
	if (_selectedObject != nullptr)
	{
		_selectedObject->setMaterial(new material(
			glm::vec3(atof(matkax->value()), atof(matkay->value()), atof(matkaz->value())),
			glm::vec3(atof(matkdx->value()), atof(matkdy->value()), atof(matkdz->value())),
			glm::vec3(atof(matksx->value()), atof(matksy->value()), atof(matksz->value())),
			180.0f));

		this->redraw();
	}
	else
		updateSelected(_selectedObject);
}

void MyGlWindow::spawnSimpleObject()
{
	if (currentSimpleObjectName == "Sphere")
	{
		_objectList.push_back(new Sphere(1.0, 60, 60, new PhongShader(), _lightManager));
		browser->add("Sphere");
	}
	this->redraw();
}

void MyGlWindow::updateSelected(IDrawable * drawable)
{
	_selectedObject = drawable;

	if (drawable != nullptr)
	{
		// Update position editor
		posx->value(std::to_string(_selectedObject->getPosition().x).c_str());
		posy->value(std::to_string(_selectedObject->getPosition().y).c_str());
		posz->value(std::to_string(_selectedObject->getPosition().z).c_str());

		// Update material editor
		matkax->value(std::to_string(_selectedObject->getMaterial()->getKa().x).c_str());
		matkay->value(std::to_string(_selectedObject->getMaterial()->getKa().y).c_str());
		matkaz->value(std::to_string(_selectedObject->getMaterial()->getKa().z).c_str());

		matkdx->value(std::to_string(_selectedObject->getMaterial()->getKd().x).c_str());
		matkdy->value(std::to_string(_selectedObject->getMaterial()->getKd().y).c_str());
		matkdz->value(std::to_string(_selectedObject->getMaterial()->getKd().z).c_str());

		matksx->value(std::to_string(_selectedObject->getMaterial()->getKs().x).c_str());
		matksy->value(std::to_string(_selectedObject->getMaterial()->getKs().y).c_str());
		matksz->value(std::to_string(_selectedObject->getMaterial()->getKs().z).c_str());
	}
	else
	{
		// Update position editor
		posx->value("");
		posy->value("");
		posz->value("");

		// Update material editor
		matkax->value("");
		matkay->value("");
		matkaz->value("");

		matkdx->value("");
		matkdy->value("");
		matkdz->value("");

		matksx->value("");
		matksy->value("");
		matksz->value("");
	}
}

MyGlWindow::MyGlWindow(int x, int y, int w, int h)
: Fl_Gl_Window(x, y, w, h)
//==========================================================================
{	
	_selectedObject = nullptr;
	currentSimpleObjectName = "";

	browser = new Fl_Browser(w + 20, 80, 250, h/2 - 30);
	browser->type(FL_HOLD_BROWSER);
	browser->callback(ChangeSelectionCallback, (void *)this);

	Fl_Button *buttonAddModel = new Fl_Button(w + 20, 10, 115, 30, "Load a model");
	buttonAddModel->callback(AddModelCallback, (void *)this);

	Fl_Button *buttonDeleteModel = new Fl_Button(w + 140, 10, 125, 30, "Delete a model");
	buttonDeleteModel->callback(DeleteModelCallback, (void *)this);

	choiceSimpleObjectSpawner = new Fl_Choice(w + 115, 50, 125, 20, "Simple object");
	choiceSimpleObjectSpawner->add("Sphere");
	choiceSimpleObjectSpawner->callback(changeSimpleObjectSelection, (void *)this);

	Fl_Button *buttonAddChoice = new Fl_Button(w + 250, 50, 15, 20, "+");
	buttonAddChoice->callback(AddSimpleObjectCallback, (void *)this);

	/*
	** Position Editor
	*/
	// Ka
	Fl_Output *posl = new Fl_Output(w + 80, h / 2 + 75, 0, 0, "Pos:");
	posx = new Fl_Float_Input(w + 100, h / 2 + 60, 50, 30, "");
	posx->callback(ChangePositionCallback, (void *)this);
	posy = new Fl_Float_Input(w + 160, h / 2 + 60, 50, 30, "");
	posy->callback(ChangePositionCallback, (void *)this);
	posz = new Fl_Float_Input(w + 220, h / 2 + 60, 50, 30, "");
	posz->callback(ChangePositionCallback, (void *)this);
	/* !Position Editor */
	
	/*
	** Material Editor
	*/
	// Ka
	Fl_Output *matkal = new Fl_Output(w + 80, h / 2 + 115, 0, 0, "Ka:");
	matkax = new Fl_Float_Input(w + 100, h / 2 + 100, 50, 30, "");
	matkax->callback(ChangeMaterialCallback, (void *)this);
	matkay = new Fl_Float_Input(w + 160, h / 2 + 100, 50, 30, "");
	matkay->callback(ChangeMaterialCallback, (void *)this);
	matkaz = new Fl_Float_Input(w + 220, h / 2 + 100, 50, 30, "");
	matkaz->callback(ChangeMaterialCallback, (void *)this);
	// Kd
	Fl_Output *matkdl = new Fl_Output(w + 80, h / 2 + 155, 0, 0, "Kd:");
	matkdx = new Fl_Float_Input(w + 100, h / 2 + 140, 50, 30, "");
	matkdx->callback(ChangeMaterialCallback, (void *)this);
	matkdy = new Fl_Float_Input(w + 160, h / 2 + 140, 50, 30, "");
	matkdy->callback(ChangeMaterialCallback, (void *)this);
	matkdz = new Fl_Float_Input(w + 220, h / 2 + 140, 50, 30, "");
	matkdz->callback(ChangeMaterialCallback, (void *)this);
	// Ks
	Fl_Output *matksl = new Fl_Output(w + 80, h / 2 + 195, 0, 0, "Ks:");
	matksx = new Fl_Float_Input(w + 100, h / 2 + 180, 50, 30, "");
	matksx->callback(ChangeMaterialCallback, (void *)this);
	matksy = new Fl_Float_Input(w + 160, h / 2 + 180, 50, 30, "");
	matksy->callback(ChangeMaterialCallback, (void *)this);
	matksz = new Fl_Float_Input(w + 220, h / 2 + 180, 50, 30, "");
	matksz->callback(ChangeMaterialCallback, (void *)this);
	/* !Material Editor */

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

	//m_model.glPushMatrix();
	//m_model.glTranslate(0, 1, 0);

	//if (_sphere1)
	//	_sphere1->Draw(m_model.getMatrix(), view, projection);

	if (_objectList.size() > 0)
	{
		for each (IDrawable *model in _objectList)
		{
			//m_model.glTranslate(2, 0, 0);
			m_model.glPushMatrix();
			m_model.glTranslate(model->getPosition().x, model->getPosition().y, model->getPosition().z);
			model->Draw(m_model.getMatrix(), view, projection);
			m_model.glPopMatrix();
		}
	}

	//m_model.glPopMatrix();
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

	_sphere1 = new Sphere(1.0, 60, 60, new PhongShader(), _lightManager);
	_objectList.push_back(_sphere1);
	browser->add("Sphere");
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

