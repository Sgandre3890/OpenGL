#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use() const { glUseProgram(ID); }

    // uniform helpers
    void setFloat(const std::string &name, float value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
};

#endif
