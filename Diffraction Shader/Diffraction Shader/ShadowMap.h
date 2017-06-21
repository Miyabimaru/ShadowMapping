#pragma once

#ifndef _SHADOW_MAP_H_
#define _SHADOW_MAP_H_

#include "GL/glew.h"
#include <GL/GL.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IShader.h"
#include "ShadowMapShader.h"

class ShadowMap
{
public:
	ShadowMap(glm::vec3 look, glm::vec3 up);
	~ShadowMap();

public:
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	void GenerateMap(void);
	unsigned int getFBO(void);
	unsigned int getDepthMap(void);
	IShader * getShader(void);
	IShader * getDebugShader(void);

private:
	unsigned int depthMapFBO;
	unsigned int depthMap;
	IShader * _shader;
	IShader * _debugShader;
};

#endif // !_SHADOW_MAP_H_
