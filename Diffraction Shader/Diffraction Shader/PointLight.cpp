#include "PointLight.h"

void PointLight::Initialise(IShader * shader)
{
	shader->getShaderProgram()->addUniform("PointLights[" + std::to_string(Id) + "].Position"); // Light position : vec4
	shader->getShaderProgram()->addUniform("PointLights[" + std::to_string(Id) + "].La"); // Light ambient : vec3
	shader->getShaderProgram()->addUniform("PointLights[" + std::to_string(Id) + "].Ld"); // Light diffuse : vec3
	shader->getShaderProgram()->addUniform("PointLights[" + std::to_string(Id) + "].Ls"); // Light specular : vec3
}

void PointLight::Draw(IShader * shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	glUniform4fv(shader->getShaderProgram()->uniform("PointLights[" + std::to_string(Id) + "].Position"), 1, glm::value_ptr(view * Position));
	glUniform3fv(shader->getShaderProgram()->uniform("PointLights[" + std::to_string(Id) + "].La"), 1, glm::value_ptr(La));
	glUniform3fv(shader->getShaderProgram()->uniform("PointLights[" + std::to_string(Id) + "].Ld"), 1, glm::value_ptr(Ld));
	glUniform3fv(shader->getShaderProgram()->uniform("PointLights[" + std::to_string(Id) + "].Ls"), 1, glm::value_ptr(Ls));
}

PointLight::PointLight(glm::vec4 p, glm::vec3 la, glm::vec3 ld, glm::vec3 ls, GLuint id) :
	Position(p), La(la), Ld(ld), Ls(ls), Id(id)
{
}


PointLight::~PointLight()
{
}
