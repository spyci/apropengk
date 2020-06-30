#ifndef MASHES_H
#define MASHES_H
#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <GLFW/glfw3.h>

struct Vertex {
	glm::vec3 Pos;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture{
	unsigned int Id;
	std::string Type;
	std::string Path;
};

class Mesh{
	public:
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
		std::vector<Texture> Textures;
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> texures);
	void Draw(Shader &shader);
	private:
		unsigned int VAO, VBO, EBO;
		void setupMesh();
};
#endif
