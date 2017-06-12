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
#include "IDrawable.h"
#include "IShader.h"

class Sphere : public IDrawable
{
public:
	//virtual void Initialise(IShader * shader);
	virtual void Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);
	virtual void DrawDepth(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, IShader * depthShader);

public:
	Sphere(IShader * shader, LightManager * lightManager, std::string vertexShader, std::string fragmentShader);
	Sphere(float rad, GLuint sl, GLuint st, IShader * shader, LightManager * lightManager, IShader * depthShader = nullptr);
	~Sphere();
	
	void InitShader(IShader * shad = nullptr);

	int getVertexArrayHandle();

	GLuint VAO, VBO_position, VBO_normal, VBO_tex, IBO;
	GLuint tex_2d;

	IShader * _shader;
	LightManager * _lightManager;

private:
	GLuint nVerts, elements;
	float radius;
	GLuint slices, stacks;

	void generateVerts(float *, float *, float *, GLuint *);


};


#endif
