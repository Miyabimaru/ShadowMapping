#pragma once

#ifndef _SHADOW_MAP_H_
#define _SHADOW_MAP_H_

#include "GL/glew.h"
#include <GL/GL.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

public:
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	void GenerateMap(void);
	unsigned int getFBO(void);
	unsigned int getDepthMap(void);

private:
	unsigned int depthMapFBO;
	unsigned int depthMap;
};

#endif // !_SHADOW_MAP_H_
