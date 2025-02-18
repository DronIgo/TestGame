#include "model.h"

//for optimization
namespace {
	std::vector<Texture> loadedTextures;
}

void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}

void Model::loadModel(std::string path)
{
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/')) + "/";

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int texCount = mesh->GetNumUVChannels();
	std::vector<VertexElement> elements(2 + texCount);
	elements[0] = VertexElement{ 3, GL_FLOAT, false, ElementType::XYZ };
	elements[1] = VertexElement{ 3, GL_FLOAT, false, ElementType::NORMAL };
	for (int i = 0; i < texCount; ++i)
		elements[2 + i] = VertexElement{ 2, GL_FLOAT, false, ElementType::UV };

	const VertexSpecification* spec = VertexSpecificationManager::instance().CreateVertexSpecification(elements);

	vertices.resize(mesh->mNumVertices * spec->getTotalSize());
	indices.resize(mesh->mNumFaces * 3);

	unsigned int vc = 0;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		//Position
		vertices[vc++] = mesh->mVertices[i].x;
		vertices[vc++] = mesh->mVertices[i].y;
		vertices[vc++] = mesh->mVertices[i].z;

		//Normal
		vertices[vc++] = mesh->mNormals[i].x;
		vertices[vc++] = mesh->mNormals[i].y;
		vertices[vc++] = mesh->mNormals[i].z;

		//Textures
		for (int t = 0; t < texCount; ++t)
		{
			vertices[vc++] = mesh->mTextureCoords[t][i].x;
			vertices[vc++] = mesh->mTextureCoords[t][i].y;
		}
	}
	// process indices
	unsigned int ic = 0;
	for (int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace& face = mesh->mFaces[i];
		for (int j = 0; j < 3; ++j)
			indices[ic++] = face.mIndices[j];
	}
	// process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, Texture::TYPE::DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, Texture::TYPE::SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(std::move(vertices), std::move(indices), std::move(textures), std::string(mesh->mName.C_Str()), spec);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, Texture::TYPE type)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
	{
		aiString path;
		mat->GetTexture(aiType, i, &path);
		bool alreadyLoaded = false;
		for (auto& tex : loadedTextures)
			if (std::strcmp(tex.path.c_str(), (directory + path.C_Str()).c_str()) == 0) {
				alreadyLoaded = true;
				textures.push_back(tex);
				break;
			}
		if (!alreadyLoaded) {
			Texture texture(directory, std::string(path.C_Str()), type);
			texture.type = type;
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}

	return textures;
}
