#pragma once

#ifndef _ILIGHT_H_
#define _ILIGHT_H_

#include "IShader.h"
#include <glm\glm.hpp>

class ILight
{
public:
	ILight();
	~ILight();

public:
	virtual void Initialise(IShader * shader) = 0;
	virtual void Draw(IShader * shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) = 0;
};

#endif // !_ILIGHT_H_
