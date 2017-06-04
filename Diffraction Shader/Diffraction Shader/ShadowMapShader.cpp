#include "ShadowMapShader.h"

void ShadowMapShader::Initialise()
{
	_shaderProgram = new ShaderProgram();
	_shaderProgram->initFromFiles("shadow_map.vert", "shadow_map.frag");

	//add attributes and uniform vars
	_shaderProgram->addAttribute("vertexPosition");
	_shaderProgram->addAttribute("vertexNormal");
	_shaderProgram->addUniform("ModelViewMatrix"); // View*Model : mat4
	_shaderProgram->addUniform("normalMatrix"); // Normal Matrix : mat3
	_shaderProgram->addUniform("MVP"); // Projection * View * Model : mat4

	/*
	** Shadow Map Texture Generation
	*/
	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapShader::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
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

ShadowMapShader::ShadowMapShader()
{
}


ShadowMapShader::~ShadowMapShader()
{
}
