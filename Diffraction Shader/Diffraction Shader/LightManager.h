#pragma once

#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include "PointLight.h"

class LightManager
{
public:
	LightManager();
	~LightManager();

public:
	void addPointLight(PointLight * light);

private:
	PointLight * _pointLights[5];
};

#endif // !_LIGHT_MANAGER_H_
