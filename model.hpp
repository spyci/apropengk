#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"
#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "mashes.hpp"
#include <vector>
#include <string>
#include <GLFW/glfw3.h>

unsigned int TextureFromFile(const char *path, const std::string &directory);

class Model
{
  public:
    Model(char *path);
    void Draw(Shader &shader);
  private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures (aiMaterial *mat, aiTextureType type, std::string typeName);
};
#endif
