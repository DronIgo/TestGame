#include "shader.h"

unsigned int Shader::currentActiveShader = 0;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const VertexSpecification* spec) : specification(spec)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    infoLog[0] = '\0';

    // vertex Shader
    vertex = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vShaderCode);
    if (!vertex) {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
    }
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    if (infoLog[0] != '\0') {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED_SPECIFIC\n" << infoLog << std::endl;
    }
    //glShaderSource(vertex, 1, &vShaderCode, NULL);
    //glCompileShader(vertex);
    //// print compile errors if any
    //glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    //};

    // fragment Shader
    fragment = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fShaderCode);
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    if (!fragment || infoLog[0] != '\0') {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //glShaderSource(fragment, 1, &fShaderCode, NULL);
    //glCompileShader(fragment);
    //// print compile errors if any
    //glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    //};

    // shader Program
    glCreateProgramPipelines(1, &pipelineID);
    //glAttachShader(ID, vertex);
    //glAttachShader(ID, fragment);
    //glLinkProgram(ID);
    // print linking errors if any
    //glGetProgramiv(ID, GL_LINK_STATUS, &success);
    //if (!success)
    //{
    //    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    //}

    // delete the shaders as they're linked into our program now and no longer necessary
    //glDeleteShader(vertex);
    //glDeleteShader(fragment);
}

void Shader::use()
{
    glBindProgramPipeline(pipelineID);
    currentActiveShader = pipelineID;
    glUseProgramStages(pipelineID, GL_VERTEX_SHADER_BIT, vertexID);
    glUseProgramStages(pipelineID, GL_FRAGMENT_SHADER_BIT, fragmentID);
    for (auto& [k, v] : uniformCommands) {
        setUniform(k, v);
    }
    uniformCommands.clear();
}

bool Shader::isActive() const
{
    return currentActiveShader == pipelineID;
}

bool Shader::checkUniformPresent(const std::string& name, int& location, bool& vertex_shader) const
{
    location = glGetUniformLocation(vertexID, name.c_str());
    if (location == -1) {
        location = glGetUniformLocation(fragmentID, name.c_str());
        if (location == -1) 
            return false;
        else {
            vertex_shader = false;
            return true;
        }
    }
    else {
        vertex_shader = true;
        return true;
    }
}

void Shader::setUniform(int location, uniformValue& value) {
    unsigned int shaderId = value.vertex ? vertexID : fragmentID;
    switch (value.state) {
    case uniformValue::val_state::b:
        glProgramUniform1i(shaderId, location, (int)value.value.b);
        break;
    case uniformValue::val_state::i:
        glProgramUniform1i(shaderId, location, value.value.i);
        break;
    case uniformValue::val_state::f:
        glProgramUniform1f(shaderId, location, value.value.f);
        break;
    case uniformValue::val_state::v3:
        glProgramUniform3f(shaderId, location, value.value.v3.x, value.value.v3.y, value.value.v3.z);
        break;
    case uniformValue::val_state::m44:
        glProgramUniformMatrix4fv(shaderId, location, 1, false, glm::value_ptr(value.value.m44));
        break;
    default:
        break;
    }
}

void Shader::setBool(const std::string& name, bool value)
{
    int location;
    bool vertex = false;
    if (!checkUniformPresent(name, location, vertex)) {
        std::cout << "ERROR::SHADER::setBool: uniform " << name << " doesn't exist!\n";
        return;
    }
    if (isActive())
        glProgramUniform1i(vertex ? vertexID : fragmentID, location, (int)value);
    else {
        uniformValue val;
        val.value.b = value;
        val.state = uniformValue::val_state::b;
        val.vertex = vertex;
        uniformCommands[location] = val;
    }
}
void Shader::setInt(const std::string& name, int value)
{
    int location;
    bool vertex = false;
    if (!checkUniformPresent(name, location, vertex)) {
        std::cout << "ERROR::SHADER::setInt: uniform " << name << " doesn't exist!\n";
        return;
    }
    if (isActive())
        glProgramUniform1i(vertex ? vertexID : fragmentID, location, value);
    else {
        uniformValue val;
        val.value.i = value;
        val.state = uniformValue::val_state::i;
        val.vertex = vertex;
        uniformCommands[location] = val;
    }
}
void Shader::setFloat(const std::string& name, float value)
{
    int location;
    bool vertex = false;
    if (!checkUniformPresent(name, location, vertex)) {
        std::cout << "ERROR::SHADER::setFloat: uniform " << name << " doesn't exist!\n";
        return;
    }
    if (isActive())
        glProgramUniform1f(vertex ? vertexID : fragmentID, location, value);
    else {
        uniformValue val;
        val.value.f = value;
        val.state = uniformValue::val_state::f;
        val.vertex = vertex;
        uniformCommands[location] = val;
    }
}

void Shader::setFloat3(const std::string& name, float value1, float value2, float value3)
{
    int location;
    bool vertex = false;
    if (!checkUniformPresent(name, location, vertex)) {
        std::cout << "ERROR::SHADER::Float3: uniform " << name << " doesn't exist!\n";
        return;
    }
    if (isActive())
        glProgramUniform3f(vertex ? vertexID : fragmentID, location, value1, value2, value3);
    else {
        uniformValue val;
        val.value.v3 = glm::vec3(value1, value2, value3);
        val.state = uniformValue::val_state::v3;
        val.vertex = vertex;
        uniformCommands[location] = val;
    }
}

void Shader::setFloat3(const std::string& name, const glm::vec3& value)
{
    int location;
    bool vertex;
    if (!checkUniformPresent(name, location, vertex)) {
        std::cout << "ERROR::SHADER::Float3: uniform " << name << " doesn't exist!\n";
        return;
    }
    if (isActive())
        glProgramUniform3f(vertex ? vertexID : fragmentID, location, value.x, value.y, value.z);
    else {
        uniformValue val;
        val.value.v3 = value;
        val.state = uniformValue::val_state::v3;
        val.vertex = vertex;
        uniformCommands[location] = val;
    }
}

void Shader::setMat4f(const std::string& name, const glm::mat4x4& value)
{
    int location;
    bool vertex;
    if (!checkUniformPresent(name, location, vertex)) {
        std::cout << "ERROR::SHADER::setMat4f: uniform " << name << " doesn't exist!\n";
        return;
    }
    if (isActive())
        glProgramUniformMatrix4fv(vertex ? vertexID : fragmentID, location, 1, false, glm::value_ptr(value));
    else {
        uniformValue val;
        val.value.m44 = value;
        val.state = uniformValue::val_state::m44;
        val.vertex = vertex;
        uniformCommands[location] = val;
    }
}
