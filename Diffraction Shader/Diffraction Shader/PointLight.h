#pragma once

#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Loader.h"
#include <vector>

class PointLight
{
public:
	struct s_pointlight {
		glm::vec4 Position;
		glm::vec3 La;
		glm::vec3 Ld;
		glm::vec3 Ls;

		s_pointlight(glm::vec4 p, glm::vec3 la, glm::vec3 ld, glm::vec3 ls);
	};

public:
	PointLight();
	~PointLight();
};

#endif // !POINT_LIGHT_H_
