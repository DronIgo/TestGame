#include "mesh.h"
#include <string>

Mesh::Mesh(std::vector<float>&& _vertices, std::vector<unsigned int>&& _indices, 
			std::vector<Texture>&& _textures, const std::string& _name, const VertexSpecification* _spec) : name(_name), spec(_spec)
{
	vertices = _vertices;
	indices = _indices;
	textures = _textures;
	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < 1; ++i)//textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		Texture::TYPE type = textures[i].type;
		std::string name;
		if (type == Texture::TYPE::DIFFUSE) {
			number = std::to_string(diffuseNr++);
			name = Texture::textureDiffuseName;
		}
		else if (type == Texture::TYPE::SPECULAR) {
			number = std::to_string(specularNr++);
			name = Texture::textureSpecularName;
		}

		shader.setInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}

	// draw mesh
	vao.bind();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::print()
{
	std::cout << "Mesh name: " << name << std::endl;
	std::cout << "Verticies: " << vertices.size() << std::endl;
	std::cout << "Indices: " << indices.size() << std::endl;

	std::cout << std::endl;
}

void Mesh::setupMesh()
{
	vao.bufferData((float*) &vertices[0], sizeof(vertices), 
				   &indices[0], indices.size() * sizeof(unsigned int));
	vao.setVertexSpecification(spec);
}

