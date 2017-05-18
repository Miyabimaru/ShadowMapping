#pragma once

#ifndef _IDRAWABLE_H_
#define _IDRAWABLE_H_

#include "material.h"
#include <glm\glm.hpp>

class IDrawable
{
public:
	virtual ~IDrawable();

public:
	virtual void Initialise() = 0;
	virtual void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) = 0;
};

#endif // !_IDRAWABLE_H_
