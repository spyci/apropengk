#include "../headers/mashes.hpp"
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, 
								std::vector<Texture> texture)
{
	this->Vertices = vertices;
	this->Indices = indices;
	this->Textures = texture;
	setupMesh();
}
void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(Vertex), 
									&this->Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(unsigned int), 
									&this->Indices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
									(void*)offsetof(Vertex, Pos));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
									(void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
									(void*)offsetof(Vertex, TexCoords));
}
void Mesh::Draw(Shader &shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for(unsigned int i = 0; i < this->Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = Textures[i].Type;
		if(name == "texture_diffuse")
						number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
						number = std::to_string(specularNr++);
		shader.setInt((name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, this->Textures[i].Id);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}
