#ifndef ___SPHERE_H
#define ___SPHERE_H

#include "GL/glew.h"
#include <GL/GL.h>
#include <glm/mat4x4.hpp>

#include <vector>
#include <SOIL/SOIL.h>

#include "Loader.h"
#include "LightManager.h"
#include "material.h"


class Sphere
{
public:
	Sphere(LightManager * lightManager, std::string vertexShader, std::string fragmentShader);
	Sphere(float rad, GLuint sl, GLuint st, LightManager * lightManager, std::string vertexShader, std::string fragmentShader);
	~Sphere();

	void setup();
	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);
	int getVertexArrayHandle();

	GLuint VAO, VBO_position, VBO_normal, VBO_tex, IBO;
	GLuint tex_2d;

	ShaderProgram *shaderProgram;

	LightManager * _lightManager;
	material * _material;

private:
	GLuint nVerts, elements;
	float radius;
	GLuint slices, stacks;

	void generateVerts(float *, float *, float *, GLuint *);


};


#endif
