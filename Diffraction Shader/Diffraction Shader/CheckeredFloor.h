#ifndef __CHECKEREDFLOOR
#define __CHECKEREDFLOOR

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "Loader.h"
#include <vector>

class checkeredFloor
{
public:
	checkeredFloor();
	void setup(float size, int nSquares);
	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);

	GLuint vaoHandle;
	GLuint vbo_cube_vertices, vbo_cube_colors;
	ShaderProgram *shaderProgram;

};

#endif