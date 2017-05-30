#include "material.h"



material::material(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, GLfloat shiness) :
	Ka(ka), Kd(kd), Ks(ks), Shiness(shiness)
{
}


material::~material()
{
}

void material::setup(IShader * shader)
{
	shader->getShaderProgram()->addUniform("Material.Ka"); // Ambient reflectivity : vec3
	shader->getShaderProgram()->addUniform("Material.Kd"); // Diffuse reflectivity : vec3
	shader->getShaderProgram()->addUniform("Material.Ks"); // Specular reflectivity : vec3
	shader->getShaderProgram()->addUniform("Material.Shiness"); // Specular shiness factor : float
}

void material::draw(IShader * shader, glm::mat4 & view)
{
	glUniform3fv(shader->getShaderProgram()->uniform("Material.Ka"), 1, glm::value_ptr(Ka));
	glUniform3fv(shader->getShaderProgram()->uniform("Material.Kd"), 1, glm::value_ptr(Kd));
	glUniform3fv(shader->getShaderProgram()->uniform("Material.Ks"), 1, glm::value_ptr(Ks));
	glUniform1fv(shader->getShaderProgram()->uniform("Material.Shiness"), 1, &Shiness);
}

glm::vec3 material::getKa(void)
{
	return Ka;
}

glm::vec3 material::getKd(void)
{
	return Kd;
}

glm::vec3 material::getKs(void)
{
	return Ks;
}
