#pragma once
#include "shader.h"
#include <vector>
#include <string>
#include <filesystem>
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(std::filesystem::path path)
    {
        loadModel(path);
        //for (Mesh& mesh : meshes) {
        //    mesh.print();
        //}
    }
    void Draw(Shader shader);

private:
    // model data
    std::vector<Mesh> meshes;
    std::filesystem::path directory;
    Assimp::Importer importer;

    void loadModel(std::filesystem::path& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, Texture::TYPE type);
};