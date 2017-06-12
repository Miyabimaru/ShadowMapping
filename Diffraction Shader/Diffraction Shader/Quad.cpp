#ifndef ___QUAD_H
#define ___QUAD_H

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

class Quad : public IDrawable
{
public:
	//virtual void Initialise(IShader * shader);
	virtual void Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);
	virtual void DrawDepth(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, IShader * depthShader);

public:
	Quad(IShader * shader, LightManager * lightManager, std::string vertexShader, std::string fragmentShader);
	Quad(IShader * shader, LightManager * lightManager, IShader * depthShader = nullptr);
	~Quad();

	void InitShader(IShader * shad = nullptr);

	GLuint quadVAO, quadVBO;

	IShader * _shader;
	LightManager * _lightManager;

private:
	float quadVertices[];

	void generateVerts(float *, float *, float *, GLuint *);
};


#endif