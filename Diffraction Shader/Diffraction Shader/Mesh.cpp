#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, material * mat)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	shaderProgram = new ShaderProgram();
	if (this->textures.size() > 0)
	{
		shaderProgram->initFromFiles("modelLoader.vert", "modelLoaderTexture.frag");
		shaderProgram->addUniform("texture_diffuse1");
		shaderProgram->addUniform("texture_specular1");
	}
	else
		shaderProgram->initFromFiles("modelLoader.vert", "modelLoader.frag");

	//if (mat != nullptr) mat->setup();

	shaderProgram->addUniform("NormalMatrix");
	shaderProgram->addUniform("LightPosition");  //Light Position
	shaderProgram->addUniform("LightIntensity"); //Is = Id = Ia = LightIntensity
	shaderProgram->addUniform("ModelViewMatrix");  //View*Model : mat4
	shaderProgram->addUniform("MVP");
	shaderProgram->addUniform("Ka");
	shaderProgram->addUniform("Kd");
	shaderProgram->addUniform("Ks");
	shaderProgram->addUniform("Shiness");

	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);  //VAO
	glGenBuffers(1, &this->VBO);  //VBO for position
	glGenBuffers(1, &this->EBO);  //VBO for index
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));
	// Vertex Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));
	// Vertex Bit Tangeant
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));
	glBindVertexArray(0);
}

void Mesh::draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, material * mat)
{
	glm::mat4 mview = view * model;
	glm::mat4 mvp = projection * view * model;
	glm::vec4 lightPos(10, 10, 10, 0);
	glm::vec3 LightIntensity(0.8, 0.8, 0.8);

	glm::vec3 Ka(0.9, 0.9, 0.9);
	//glm::vec3 Kd(0.8, 0.8, 0.8);
	glm::vec3 Ks(0.1, 0.1, 0.1);

	GLfloat shiness = 3.0f;

	glm::mat4 imvp = glm::inverse(mview);
	glm::mat3 nmat = glm::mat3(glm::transpose(imvp));

	shaderProgram->use();

	//if (mat != nullptr) mat->draw();

	glUniformMatrix4fv(shaderProgram->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mview));
	glUniformMatrix3fv(shaderProgram->uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(nmat));
	glUniformMatrix4fv(shaderProgram->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

	glUniform4fv(shaderProgram->uniform("LightPosition"), 1, glm::value_ptr(view * lightPos));
	glUniform3fv(shaderProgram->uniform("LightIntensity"), 1, glm::value_ptr(LightIntensity));

	glUniform3fv(shaderProgram->uniform("Ka"), 1, glm::value_ptr(Ka));
	//glUniform3fv(shaderProgram->uniform("Kd"), 1, glm::value_ptr(Kd));
	glUniform3fv(shaderProgram->uniform("Ks"), 1, glm::value_ptr(Ks));
	glUniform1fv(shaderProgram->uniform("Shiness"), 1, &shiness);

	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();
		glUniform1f(shaderProgram->uniform((name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shaderProgram->disable();
}