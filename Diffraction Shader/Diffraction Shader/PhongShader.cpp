#include "PhongShader.h"

void PhongShader::Initialise()
{
	_shaderProgram = new ShaderProgram();
	_shaderProgram->initFromFiles("simple_phong.vert", "simple_phong.frag");

	std::cout << "mdr init phong" << std::endl;

	//add attributes and uniform vars
	_shaderProgram->addAttribute("vertexPosition");
	_shaderProgram->addAttribute("vertexNormalTRUC");
	_shaderProgram->addAttribute("VertexTexCoord");
	_shaderProgram->addUniform("ModelViewMatrix"); // View*Model : mat4
	_shaderProgram->addUniform("normalMatrix"); // Normal Matrix : mat3
	_shaderProgram->addUniform("model"); // Model Matrix : mat4
	_shaderProgram->addUniform("MVP"); // Projection * View * Model : mat4

	_shaderProgram->addUniform("depthMap");
	_shaderProgram->addUniform("lightSpaceMatrix"); // Light Point of view : mat4
}

void PhongShader::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	float near_plane = 1.0f, far_plane = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;


	glm::mat4 mview = view * model;
	glm::mat4 mvp = projection * view * model;

	glm::mat4 inverseModelView = glm::inverse(mview);
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseModelView));

	_shaderProgram->use();

	glUniformMatrix4fv(_shaderProgram->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mview));
	glUniformMatrix3fv(_shaderProgram->uniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(_shaderProgram->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
	glUniformMatrix4fv(_shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));

	glUniform1f(_shaderProgram->uniform("near_plane"), near_plane);
	glUniform1f(_shaderProgram->uniform("far_plane"), far_plane);
	glUniformMatrix4fv(_shaderProgram->uniform("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
}

PhongShader::PhongShader()
{
}


PhongShader::~PhongShader()
{
	if (_shaderProgram) delete _shaderProgram;
}
