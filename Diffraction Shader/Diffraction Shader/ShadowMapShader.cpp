#include "ShadowMapShader.h"

void ShadowMapShader::Initialise()
{
	_shaderProgram = new ShaderProgram();
	_shaderProgram->initFromFiles("shadow_map.vert", "shadow_map.frag");

	//add attributes and uniform vars
	_shaderProgram->use();
	_shaderProgram->addUniform("lightSpaceMatrix"); // Light Point of view : mat4
	_shaderProgram->addUniform("model"); // Model : mat4
}

void ShadowMapShader::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	float near_plane = 1.0f, far_plane = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	_shaderProgram->use();

	glUniformMatrix4fv(_shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_shaderProgram->uniform("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
}

ShadowMapShader::ShadowMapShader()
{
}


ShadowMapShader::~ShadowMapShader()
{
	if (_shaderProgram) delete _shaderProgram;
}
