#include "DebugTexture.h"



DebugTexture::DebugTexture(LightManager * lightManager)
{
	_lightManager = lightManager;
}


DebugTexture::~DebugTexture()
{
}

void DebugTexture::Initialise(IShader * shader)
{
	IDrawable::Initialise(shader);

	this->setMaterial(new material(
		glm::vec3(.1, .1, .1),
		glm::vec3(.9, .9, .9),
		glm::vec3(.9, .9, .9),
		180.0f));

	//Shader
	if (_shader) _shader->Initialise();

	// Lights
	if (_lightManager) _lightManager->Initialise(_shader);

	//Material
	if (_material) _material->setup(_shader);

	//create vao
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//_shader->getShaderProgram()->addUniform("Tex1");

	// Vertices
	float v[] = {
		1.0f, 0.0f,  1.0f,
		-1.0f, 0.0f,  1.0f,
		-1.0f, 0.0f, -1.0f,

		1.0f, 0.0f,  1.0f,
		-1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f
	};
	// Normals
	float n[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// Tex coords
	float tex[] = {
		1.0f,  1.0f,
		1.0f,  0.0f,
		0.0f, 0.0f,

		1.0f,  1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	//create vbo for vertices
	glGenBuffers(1, &VBO_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 6, v, GL_STATIC_DRAW);
	glVertexAttribPointer(
		_shader->getShaderProgram()->attribute("vertexPosition"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(_shader->getShaderProgram()->attribute("vertexPosition"));

	//create vbo for normals
	glGenBuffers(1, &VBO_normal);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 3, n, GL_STATIC_DRAW);

	glVertexAttribPointer(
		_shader->getShaderProgram()->attribute("vertexNormalTRUC"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(_shader->getShaderProgram()->attribute("vertexNormalTRUC"));

	// Create VBO for texture
	glGenBuffers(1, &VBO_tex);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, tex, GL_STATIC_DRAW);
	glVertexAttribPointer(
		_shader->getShaderProgram()->attribute("VertexTexCoord"), // attribute
		2,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(_shader->getShaderProgram()->attribute("VertexTexCoord"));

	//glGenBuffers(1, &IBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements, el, GL_STATIC_DRAW);

	glBindVertexArray(0);

	_shader->getShaderProgram()->disable();
}

void DebugTexture::Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection)
{
	if (_shader) _shader->Draw(model, view, projection);
	if (_lightManager) _lightManager->Draw(_shader, model, view, projection);
	if (_material) _material->draw(_shader, view);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	_shader->getShaderProgram()->disable();
	
}

void DebugTexture::DrawDepth(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, IShader * depthShader)
{
}
