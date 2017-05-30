#include "IDrawable.h"

IDrawable::~IDrawable()
{
}

void IDrawable::Initialise(IShader * shader)
{
	_shader = shader;
}

material * const IDrawable::getMaterial(void)
{
	return _material;
}

void IDrawable::setMaterial(material * mat)
{
	if (_material != nullptr)
		delete _material;
	_material = mat;
}

std::string IDrawable::getName(void)
{
	return _name;
}
