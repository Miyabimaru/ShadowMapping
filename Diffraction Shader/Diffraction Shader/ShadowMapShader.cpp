#include "ShadowMapShader.h"

void ShadowMapShader::Initialise()
{
	_shaderProgram = new ShaderProgram();
	if (_debug)
		_shaderProgram->initFromFiles("debug_shadow_map.vert", "debug_shadow_map.frag");
	else
		_shaderProgram->initFromFiles("shadow_map.vert", "shadow_map.frag");

	//add attributes and uniform vars
	_shaderProgram->use();
	_shaderProgram->addAttribute("vertexPosition");
	_shaderProgram->addAttribute("vertexNormalTRUC");
	_shaderProgram->addAttribute("VertexTexCoord");
	_shaderProgram->addUniform("lightSpaceMatrix"); // Light Point of view : mat4
	_shaderProgram->addUniform("model"); // Model : mat4
	_shaderProgram->addUniform("depthMap");
	_shaderProgram->addUniform("near_plane");
	_shaderProgram->addUniform("far_plane");

	if (_debug)
		_shaderProgram->addUniform("MVP");
}

void ShadowMapShader::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	float near_plane = 1.0f, far_plane = 150.0f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	glm::mat4 lightView = glm::lookAt(glm::vec3(5.0f, 5.0f, 5.0f),
		_look,
		_up);

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	glm::mat4 mvp = projection * view * model;

	_shaderProgram->use();

	if (_debug)
		std::cout << "DRAW EN DEBUG" << std::endl;

	if (_debug)
		glUniformMatrix4fv(_shaderProgram->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
	glUniform1f(_shaderProgram->uniform("near_plane"), near_plane);
	glUniform1f(_shaderProgram->uniform("far_plane"), far_plane);
	glUniformMatrix4fv(_shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_shaderProgram->uniform("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
}

ShadowMapShader::ShadowMapShader(glm::vec3 look, glm::vec3 up, bool debug) : _look(look), _up(up), _debug(debug)
{
}


ShadowMapShader::~ShadowMapShader()
{
	if (_shaderProgram) delete _shaderProgram;
}
