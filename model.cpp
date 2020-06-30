#include "../headers/model.hpp"
Model::Model(char *path)
{
  loadModel(path);
}
void Model::Draw(Shader &shader)
{
  for(unsigned int i = 0; i < meshes.size(); i++)
    meshes[i].Draw(shader);
}
void Model::loadModel(std::string path)
{
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
	   std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
     return;
  }
  directory = path.substr(0, path.find_last_of('/'));
  processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene)
{
  for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
	   aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
	    meshes.push_back(processMesh(mesh, scene));
	}
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> texture;
  //process vertices
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
	   Vertex vertex;
     glm::vec3 Pos;
     Pos.x = mesh->mVertices[i].x;
     Pos.y = mesh->mVertices[i].y;
     Pos.z = mesh->mVertices[i].z;
     vertex.Pos = Pos;
     glm::vec3 Normal;
     Normal.x = mesh->mVertices[i].x;
     Normal.y = mesh->mVertices[i].y;
     Normal.z = mesh->mVertices[i].z;
     vertex.Normal = Normal;
     if(mesh->mTextureCoords[0])
     {
       glm::vec2 TexCoords;
       TexCoords.x = mesh->mTextureCoords[0][i].x;
       TexCoords.y = mesh->mTextureCoords[0][i].y;
       vertex.TexCoords = TexCoords;
     }
     else
       vertex.TexCoords = glm::vec2 (0.0f, 0.0f);
   }
	//Texture Coords

	//Indices
  for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
	   aiFace Face = mesh->mFaces[i];
     for(unsigned int j = 0; j < Face.mNumIndices; j++)
     {
       indices.push_back(Face.mIndices[j]);
     }
  }
	if(mesh->mMaterialIndex >= 0)
	{
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    texture.insert(texture.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    texture.insert(texture.end(), specularMaps.begin(), specularMaps.end());
	}
}
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
  std::vector<Texture> textures;
  for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
  {
    aiString str;
    mat->GetTexture(type, i, &str);
    Texture texture;
    texture.Id = TextureFromFile(str.C_Str(), directory);
    texture.Type = typeName;
    texture.Path = str.C_Str();
    textures.push_back(texture);
  }
  return textures;
}

unsigned int TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}
