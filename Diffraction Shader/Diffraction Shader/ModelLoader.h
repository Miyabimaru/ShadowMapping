#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <stack>
#include <vector>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

GLint TextureFromFile(const char* path, std::string directory);

class ModelLoader
{
public:
	const char *fileName;

	/* Functions */
	ModelLoader(GLchar* path, const char *file)
	{
		this->fileName = file;
		this->loadModel(path);
	}
	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);
private:
	/* Model Data */
	std::vector<Mesh> meshes;
	std::string directory;
	ShaderProgram *shaderProgram;
	/* Functions */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};