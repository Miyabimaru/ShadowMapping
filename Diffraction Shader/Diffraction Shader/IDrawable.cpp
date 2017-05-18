#include "IDrawable.h"

IDrawable::~IDrawable()
{
}

std::string IDrawable::getName(void)
{
	return _name;
}
