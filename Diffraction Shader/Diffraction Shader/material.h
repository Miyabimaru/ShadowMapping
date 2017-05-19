#pragma once

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Loader.h"
#include "IShader.h"
#include <vector>

class material
{
private:
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	GLfloat Shiness;

public:
	material(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, GLfloat shiness);
	~material();

	void setup(IShader * shader);
	void draw(IShader * shader, glm::mat4 & view);
};

#endif /* !_MATERIAL_H_ */