#include "IDrawable.h"

IDrawable::~IDrawable()
{
}

void IDrawable::Initialise(IShader * shader)
{
	_shader = shader;
	_position = glm::vec3();
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

glm::vec3 const IDrawable::getPosition(void)
{
	return _position;
}

void IDrawable::setPosition(glm::vec3 pos)
{
	_position = pos;
}

std::string IDrawable::getName(void)
{
	return _name;
}
