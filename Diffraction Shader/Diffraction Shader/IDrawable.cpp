#include "IDrawable.h"

IDrawable::~IDrawable()
{
}

void IDrawable::Initialise(IShader * shader)
{
	_shader = shader;
}

std::string IDrawable::getName(void)
{
	return _name;
}
