#pragma once
#include "glad/glad.h"
#include <string>


class Texture {
private:
	int width, height, nrChannels;
	//Loads the texture from the path file
	void LoadFromFile();
public:
	static const std::string textureDiffuseName;
	static const std::string textureSpecularName;
	enum class TYPE {
		DIFFUSE,
		SPECULAR
	};
	unsigned int ID;
	TYPE type;
	std::string path;

	Texture(const std::string& filePath, const std::string& file, TYPE _type);
	Texture(const std::string& filename, TYPE _type);

	inline void bind() { glBindTexture(GL_TEXTURE_2D, ID); }
};

