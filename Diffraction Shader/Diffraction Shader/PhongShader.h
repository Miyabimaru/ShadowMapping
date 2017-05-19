#pragma once

#ifndef _PHONG_SHADER_H_
#define _PHONE_SHADER_H_

#include "GL/glew.h"
#include <GL/GL.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IShader.h"

class PhongShader : public IShader
{
public:
	virtual void Initialise();
	virtual void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

public:
	PhongShader();
	~PhongShader();
};


#endif // !_PHONG_SHADER_H_
