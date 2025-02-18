#pragma once
#include "shader.h"
#include <vector>
#include <string>
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(std::string path)
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
    std::string directory;
    Assimp::Importer importer;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, Texture::TYPE type);
};