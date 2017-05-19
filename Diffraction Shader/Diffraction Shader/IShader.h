#pragma once

#ifndef _ISHADER_H_
#define _ISHADER_H_

#include "GL/glew.h"
#include <GL/GL.h>
#include <glm\glm.hpp>
#include "Loader.h"

class IShader
{
protected:
	ShaderProgram * _shaderProgram;

public:
	virtual ~IShader();
	virtual void Initialise() = 0;
	virtual void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) = 0;

public:
	ShaderProgram * getShaderProgram(void);
};

#endif /* !_ISHADER_H_ */
