#include <glm/glm.hpp>
#include "texture.h"
#include <vector>
#include "shader.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexSpecification.h"

class Mesh {
public:
    // mesh data
    std::vector<float>    vertices;
    std::vector<unsigned int>               indices;
    std::vector<Texture>                    textures;

    Mesh(std::vector<float>&& _vertices, 
         std::vector<unsigned int>&& _indices, 
         std::vector<Texture>&& _textures, 
         const std::string& _name, 
        const VertexSpecification* _spec);
    void Draw(Shader& shader);
    void print();
private:
    unsigned int numberOfTextures = 0;
    std::string name;
    const VertexSpecification* spec;
    //  render data
    VertexArray vao;

    void setupMesh();
};