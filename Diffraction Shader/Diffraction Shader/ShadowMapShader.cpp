#include "ShadowMapShader.h"

void ShadowMapShader::Initialise()
{
	_shaderProgram = new ShaderProgram();
	if (_debug)
		_shaderProgram->initFromFiles("debug_shadow_map.vert", "debug_shadow_map.frag");
	else
		_shaderProgram->initFromFiles("shadow_map.vert", "shadow_map.frag");

	//add attributes and uniform vars
	_shaderProgram->use();
	_shaderProgram->addAttribute("vertexPosition");
	_shaderProgram->addAttribute("VertexTexCoord");
	_shaderProgram->addUniform("lightSpaceMatrix"); // Light Point of view : mat4
	_shaderProgram->addUniform("model"); // Model : mat4
	_shaderProgram->addUniform("depthMap");
	_shaderProgram->addUniform("near_plane");
	_shaderProgram->addUniform("far_plane");
}

void ShadowMapShader::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	float near_plane = 1.0f, far_plane = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	if (_debug)
	{
		float planeVertices[] = {
			// positions            // normals         // texcoords
			25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

			25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
			25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
		};
		// plane VAO
		unsigned int planeVBO;
		unsigned int planeVAO;
		glGenVertexArrays(1, &planeVAO);
		glGenBuffers(1, &planeVBO);
		glBindVertexArray(planeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindVertexArray(0);

		glBindVertexArray(planeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	_shaderProgram->use();

	glUniform1f(_shaderProgram->uniform("near_plane"), near_plane);
	glUniform1f(_shaderProgram->uniform("far_plane"), far_plane);
	glUniformMatrix4fv(_shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_shaderProgram->uniform("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
}

ShadowMapShader::ShadowMapShader(bool debug) : _debug(debug)
{
}


ShadowMapShader::~ShadowMapShader()
{
	if (_shaderProgram) delete _shaderProgram;
}
