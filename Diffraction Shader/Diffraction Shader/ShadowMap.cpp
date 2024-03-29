#include "ShadowMap.h"

ShadowMap::ShadowMap(glm::vec3 look, glm::vec3 up)
{
	_shader = new ShadowMapShader(look, up);
	_shader->Initialise();

	//_debugShader = new ShadowMapShader(true);
	//_debugShader->Initialise();
}

ShadowMap::~ShadowMap()
{
}

unsigned int ShadowMap::getFBO() {
	return depthMapFBO;
}

unsigned int ShadowMap::getDepthMap() {
	return depthMap;
}

IShader * ShadowMap::getShader(void)
{
	return _shader;
}

IShader * ShadowMap::getDebugShader(void)
{
	return _debugShader;
}

void ShadowMap::GenerateMap() {
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