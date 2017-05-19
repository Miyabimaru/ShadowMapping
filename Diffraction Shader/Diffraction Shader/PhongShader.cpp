#include "PhongShader.h"



void PhongShader::Initialise()
{
	_shaderProgram = new ShaderProgram();
	_shaderProgram->initFromFiles("simple_phong.vert", "simple_phong.frag");
}

void PhongShader::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
}

PhongShader::PhongShader()
{
}


PhongShader::~PhongShader()
{
}
