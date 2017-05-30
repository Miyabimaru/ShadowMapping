#pragma once

#ifndef _IDRAWABLE_H_
#define _IDRAWABLE_H_

#include "material.h"
#include "IShader.h"
#include "material.h"
#include <glm\glm.hpp>

class IDrawable
{
public:
	virtual ~IDrawable();

protected:
	std::string _name;
	IShader * _shader;
	material * _material;

public:
	virtual void Initialise(IShader * shader);
	virtual void Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection) = 0;

	material * const getMaterial(void);
	virtual void setMaterial(material * mat);

	std::string getName(void);
};

#endif // !_IDRAWABLE_H_
