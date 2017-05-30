#ifndef __CHECKEREDFLOOR
#define __CHECKEREDFLOOR

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "IDrawable.h"
#include "PhongShader.h"
#include "Loader.h"
#include <vector>

class checkeredFloor : public IDrawable
{
public:
	//virtual void Initialise(IShader * shader);
	virtual void Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);

public:
	checkeredFloor();
	void setup(float size, int nSquares);
	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);

	GLuint vaoHandle;
	GLuint vbo_cube_vertices, vbo_cube_colors;
	ShaderProgram *shaderProgram;

};

#endif