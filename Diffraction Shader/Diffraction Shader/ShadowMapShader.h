#pragma once

#ifndef _SHADOW_MAP_SHADER_H_
#define _SHADOW_MAP_SHADER_H_

#include "GL/glew.h"
#include <GL/GL.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IShader.h"

class ShadowMapShader : public IShader
{
private:
	glm::vec3 _look;
	glm::vec3 _up;
	bool _debug;

public:
	virtual void Initialise();
	virtual void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

public:
	ShadowMapShader(glm::vec3 look, glm::vec3 up, bool debug = false);
	~ShadowMapShader();
};


#endif // !_SHADOW_MAP_SHADER_H_
