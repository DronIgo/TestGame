#pragma once
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Graphics/Objects/VertexSpecification.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

struct uniformValue {
    union val
    {
        bool b;
        int i;
        float f;
        glm::vec3 v3;
        glm::mat4x4 m44;
    } value;
    enum class val_state {
        b, i, f, v3, m44
    } state;
    bool vertex;
};

class Shader
{
private:
    //map between uniform location and a value
    std::map<int, uniformValue> uniformCommands;
    static unsigned int currentActiveShader;
    bool checkUniformPresent(const std::string& name, int& location, bool& vertex_shader) const;
    void setUniform(int location, uniformValue& value);

    const VertexSpecification* specification;
public:
    // the program ID
    unsigned int vertexID;
    unsigned int fragmentID;
    unsigned int pipelineID;
    // constructor reads and builds the shader
    Shader(const std::string& vertexPath, const std::string& fragmentPath, const VertexSpecification* spec);
    
    // use/activate the shader
    void use();
    bool isActive() const;
    // utility uniform functions
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setFloat3(const std::string& name, float value1, float value2, float value3);
    void setFloat3(const std::string& name, const glm::vec3& value);
    void setMat4f(const std::string& name, const glm::mat4x4& value);
};