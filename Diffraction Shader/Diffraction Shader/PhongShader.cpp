#include "PhongShader.h"

void PhongShader::Initialise()
{
	_shaderProgram = new ShaderProgram();
	_shaderProgram->initFromFiles("simple_phong.vert", "simple_phong.frag");

	//add attributes and uniform vars
	_shaderProgram->addAttribute("vertexPosition");
	_shaderProgram->addAttribute("vertexNormal");
	_shaderProgram->addUniform("ModelViewMatrix"); // View*Model : mat4
	_shaderProgram->addUniform("normalMatrix"); // Normal Matrix : mat3
	_shaderProgram->addUniform("MVP"); // Projection * View * Model : mat4
}

void PhongShader::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	glm::mat4 mview = view * model;
	glm::mat4 mvp = projection * view * model;

	glm::mat4 inverseModelView = glm::inverse(mview);
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseModelView));

	_shaderProgram->use();

	glUniformMatrix4fv(_shaderProgram->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mview));
	glUniformMatrix3fv(_shaderProgram->uniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(_shaderProgram->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
}

PhongShader::PhongShader()
{
}


PhongShader::~PhongShader()
{
	if (_shaderProgram) delete _shaderProgram;
}
