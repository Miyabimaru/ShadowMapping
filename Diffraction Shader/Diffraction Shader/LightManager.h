#pragma once

#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Loader.h"
#include <vector>

#include "IDrawable.h"
#include "PointLight.h"

#define POINT_LIGHTS_COUNT (5)

class LightManager : public IDrawable
{
public:
	LightManager();
	~LightManager();

// Idrawable Functions
public:
	virtual void Initialize(ShaderProgram * shaderProgram);
	virtual void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

public:
	int getPointLightsCount();

	void addPointLight(glm::vec4 p, glm::vec3 la, glm::vec3 ld, glm::vec3 ls);

private:
	PointLight * _pointLights[POINT_LIGHTS_COUNT];
};

#endif // !_LIGHT_MANAGER_H_
