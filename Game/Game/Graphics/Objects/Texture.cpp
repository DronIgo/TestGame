#include "texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const std::string Texture::textureDiffuseName = "texture_diffuse";
const std::string Texture::textureSpecularName = "texture_specular";

Texture::Texture(const std::string& filename, TYPE _type) : type(_type)
{
	path = (std::string)("images/") + filename;
	LoadFromFile();
}

Texture::Texture(const std::string& filePath, const std::string& filename, TYPE _type) : type(_type)
{
	path = filePath + filename;
	LoadFromFile();
}

void Texture::LoadFromFile()
{
	unsigned char* data = stbi_load((path).c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
}
