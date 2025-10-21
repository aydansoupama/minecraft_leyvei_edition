//
// Created by leyve on 21/10/2025.
//

#ifndef MINECRAFT_LEYVEI_EDITION_SHADERS_H
#define MINECRAFT_LEYVEI_EDITION_SHADERS_H

#pragma once

#include <string>
#include <glad/glad.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    ~Shader();

private:
    GLuint ID;

    std::string readFile(const std::string& path);
    void checkCompileErrors(GLuint shader, const std::string& type);
};

#endif //MINECRAFT_LEYVEI_EDITION_SHADERS_H