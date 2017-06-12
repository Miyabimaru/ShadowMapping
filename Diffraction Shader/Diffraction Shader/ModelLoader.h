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
#include "IDrawable.h"

#include "PhongShader.h"

GLint TextureFromFile(const char* path, std::string directory);

class ModelLoader : public IDrawable
{
public:
	const char *fileName;

	/* Functions */
	ModelLoader(GLchar* path, const char *file)
	{
		this->fileName = file;
		this->loadModel(path, new PhongShader());
	}
	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);

// Idrawable Functions
public:
	//virtual void Initialise(IShader * shader);
	virtual void Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);
	virtual void DrawDepth(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, IShader * depthShader);

private:
	/* Model Data */
	std::vector<Mesh> meshes;
	std::string directory;
	ShaderProgram *shaderProgram;
	/* Functions */
	void loadModel(std::string path, IShader * shader);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
