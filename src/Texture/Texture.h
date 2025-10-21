//
// Created by Cline on 21/10/2025.
//

#ifndef MINECRAFT_LEYVEI_EDITION_TEXTURE_H
#define MINECRAFT_LEYVEI_EDITION_TEXTURE_H

#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture(const std::string &path);
    ~Texture();

    void bind() const;
    void bind(GLenum textureUnit) const;

    unsigned int getID() const;

private:
    unsigned int id;
};

#endif // MINECRAFT_LEYVEI_EDITION_TEXTURE_H
