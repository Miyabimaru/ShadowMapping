#include "Sphere.h"

#include <glm//gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <exception>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
Sphere::Sphere(IShader * shader, LightManager * lightManager, std::string vertexShader, std::string fragmentShader) : _lightManager(lightManager)
{
	throw new std::exception("SPHERE BAD CONSTRUCTOR");
}


Sphere::~Sphere()
{
	if (_shader) delete _shader;
	if (_material) delete _material;
}


//set rad = 1.0  sl, st = 60.
Sphere::Sphere(float rad, GLuint sl, GLuint st, IShader * shader, LightManager * lightManager, IShader * depthShader) :
radius(rad), slices(sl), stacks(st), _lightManager(lightManager)
{
	IDrawable::Initialise(shader);
	//glActiveTexture(GL_TEXTURE0);
	//glGenTextures(1, &tex_2d);
	//glBindTexture(GL_TEXTURE_2D, tex_2d);

	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	int img_h, img_w;
	unsigned char * image = SOIL_load_image("earth.jpg", &img_w, &img_h, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_w, img_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	/*_material = new material(
		glm::vec3(.1, .1, .1),
		glm::vec3(.4, .4, .4),
		glm::vec3(.9, .9, .9),
		180.0f);*/

	this->setMaterial(new material(
		glm::vec3(.1, .1, .1),
		glm::vec3(.9, .9, .9),
		glm::vec3(.9, .9, .9),
		180.0f));

	nVerts = (slices + 1) * (stacks + 1);  //the number of vertices
	elements = (slices * 2 * (stacks - 1)) * 3; 
	
	// Vertices
	float * v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];

	// Tex coords
	float * tex = new float[2 * nVerts];

	// Elements
	unsigned int * el = new unsigned int[elements];

	// Generate the vertex data : this function fill all data into the arrays.
	generateVerts(v, n, tex, el);

	_currentShaderCount = 0;
	VAO = new GLuint[MAX_SPHERE_SHADER];
	VBO_normal = new GLuint[MAX_SPHERE_SHADER];
	VBO_position = new GLuint[MAX_SPHERE_SHADER];
	VBO_tex = new GLuint[MAX_SPHERE_SHADER];
	IBO = new GLuint[MAX_SPHERE_SHADER];

	InitShader(_shader, v, n, tex, el);
	if (depthShader != nullptr)
		InitShader(depthShader, v, n, tex, el);
}

void Sphere::InitShader(IShader * shad, float * v, float * n, float * tex, unsigned int * el)
{
	if (shad == nullptr)
		shad = _shader;

	if (_currentShaderCount > MAX_SPHERE_SHADER)
		throw new std::exception("TOO MANY SHADERS IN SPHERE");

	//Shader
	if (shad) shad->Initialise();

	//light
	if (_lightManager) _lightManager->Initialise(shad);

	//Material
	if (_material) _material->setup(shad);

	//create vao
	glGenVertexArrays(1, &VAO[_currentShaderCount]);
	glBindVertexArray(VAO[_currentShaderCount]);

	//_shader->getShaderProgram()->addUniform("Tex1");

	//create vbo for vertices
	glGenBuffers(1, &VBO_position[_currentShaderCount]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[_currentShaderCount]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nVerts, v, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shad->getShaderProgram()->attribute("vertexPosition"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(shad->getShaderProgram()->attribute("vertexPosition"));

	//create vbo for normals
	glGenBuffers(1, &VBO_normal[_currentShaderCount]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal[_currentShaderCount]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVerts * 3, n, GL_STATIC_DRAW);

	glVertexAttribPointer(
		shad->getShaderProgram()->attribute("vertexNormalTRUC"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(shad->getShaderProgram()->attribute("vertexNormalTRUC"));

	// Create VBO for texture
	glGenBuffers(1, &VBO_tex[_currentShaderCount]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tex[_currentShaderCount]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * nVerts, tex, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shad->getShaderProgram()->attribute("VertexTexCoord"), // attribute
		2,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(shad->getShaderProgram()->attribute("VertexTexCoord"));

	glGenBuffers(1, &IBO[_currentShaderCount]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[_currentShaderCount]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements, el, GL_STATIC_DRAW);

	glBindVertexArray(0);

	shad->getShaderProgram()->disable();

	_currentShaderCount++;
}

void Sphere::Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection) 
{
	if (_shader) _shader->Draw(model, view, projection);

	if (_lightManager) _lightManager->Draw(_shader, model, view, projection);
	if (_material) _material->draw(_shader, view);

	//glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE0);

	//glBindTexture(GL_TEXTURE_2D, tex_2d);
	//glUniform1i(shaderProgram->uniform("Tex1"), 0);

	glBindVertexArray(VAO[0]);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//int size;
	//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);

	_shader->getShaderProgram()->disable();
}

void Sphere::DrawDepth(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, IShader * depthShader)
{
	if (depthShader)
	{
		depthShader->Draw(model, view, projection);

		glBindVertexArray(VAO[1]);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		//int size;
		//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);

		depthShader->getShaderProgram()->disable();
	}
}

void Sphere::generateVerts(float * verts, float * norms, float * tex,
	GLuint * el)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / slices;
	GLfloat phiFac = glm::pi<float>() / stacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (GLuint i = 0; i <= slices; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / slices;
		for (GLuint j = 0; j <= stacks; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / stacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = radius * nx; verts[idx + 1] = radius * ny; verts[idx + 2] = radius * nz;
			norms[idx] = nx; norms[idx + 1] = ny; norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for (GLuint i = 0; i < slices; i++) {
		GLuint stackStart = i * (stacks + 1);
		GLuint nextStackStart = (i + 1) * (stacks + 1);
		for (GLuint j = 0; j < stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == stacks - 1) {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j;
				idx += 3;
			}
			else {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j + 1;
				el[idx + 3] = nextStackStart + j;
				el[idx + 4] = stackStart + j;
				el[idx + 5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}
}

int Sphere::getVertexArrayHandle() 
{
	return this->VAO[0];
}

