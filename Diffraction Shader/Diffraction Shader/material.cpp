#include "material.h"



material::material(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, GLfloat shiness) :
	Ka(ka), Kd(kd), Ks(ks), Shiness(shiness)
{
}


material::~material()
{
}

void material::setup(ShaderProgram * shaderProgram)
{
	shaderProgram->addUniform("Material.Ka"); // Ambient reflectivity : vec3
	shaderProgram->addUniform("Material.Kd"); // Diffuse reflectivity : vec3
	shaderProgram->addUniform("Material.Ks"); // Specular reflectivity : vec3
	shaderProgram->addUniform("Material.Shiness"); // Specular shiness factor : float
}

void material::draw(ShaderProgram * shaderProgram, glm::mat4 & view)
{
	glUniform3fv(shaderProgram->uniform("Material.Ka"), 1, glm::value_ptr(Ka));
	glUniform3fv(shaderProgram->uniform("Material.Kd"), 1, glm::value_ptr(Kd));
	glUniform3fv(shaderProgram->uniform("Material.Ks"), 1, glm::value_ptr(Ks));
	glUniform1fv(shaderProgram->uniform("Material.Shiness"), 1, &Shiness);
}
