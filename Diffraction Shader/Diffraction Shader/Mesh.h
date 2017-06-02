#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <stack>
#include <vector>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <FL\Fl_Widget.H>
#include <FL\Fl_File_Chooser.H>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include <glm/mat4x4.hpp>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "material.h"

#include "Loader.h"

struct Vertex {
	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	// Tangent
	glm::vec3 Tangent;
	// BitTangent
	glm::vec3 BitTangent;
};
struct Texture {
	GLuint id;
	std::string type;  //diffuse texture or a specular texture
	aiString path;  ///texture file directory
};


class Mesh {
public:
	/* Mesh Data */
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	/* Functions */
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, material * mat);
	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, material * mat);
private:
	/* Render data */
	GLuint VAO, VBO, EBO;
	ShaderProgram *shaderProgram;
	/* Functions */
	void setupMesh();
};