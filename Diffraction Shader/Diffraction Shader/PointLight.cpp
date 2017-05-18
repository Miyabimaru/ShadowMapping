#include "PointLight.h"

PointLight::s_pointlight::s_pointlight(glm::vec4 p, glm::vec3 la, glm::vec3 ld, glm::vec3 ls) :
	Position(p), La(la), Ld(ld), Ls(ls)
{
}

PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}
