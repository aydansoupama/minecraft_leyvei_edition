//
// Created by Cline on 21/10/2025.
//

#ifndef MINECRAFT_LEYVEI_EDITION_BLOCK_H
#define MINECRAFT_LEYVEI_EDITION_BLOCK_H

#pragma once
#include <glm/glm.hpp>
#include "../Texture/Texture.h"

enum class BlockType
{
    GRASS,
    DIRT,
    STONE
};

class Block
{
public:
    Block(BlockType type, glm::vec3 pos);
    ~Block();

    void draw();
    const glm::vec3 &getPosition() const;

private:
    static constexpr int faceIDs[36] = {
        // Face 0: Front face
        0, 0, 0, 0, 0, 0,
        // Face 1: Back face
        1, 1, 1, 1, 1, 1,
        // Face 2: Left face
        2, 2, 2, 2, 2, 2,
        // Face 3: Right face
        3, 3, 3, 3, 3, 3,
        // Face 4: Top face
        4, 4, 4, 4, 4, 4,
        // Face 5: Bottom face
        5, 5, 5, 5, 5, 5
    };

    static constexpr float vertices[36 * 3] = {
        // Front face
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        // Back face
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        // Left face
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        // Right face
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        // Top face
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f};

    static constexpr float texCoords[36 * 2] = {
        // Front face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        // Back face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        // Left face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        // Right face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        // Bottom face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        // Top face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f};

    unsigned int VAO, VBO;
    Texture *topTexture;
    Texture *sideTexture;
    Texture *bottomTexture;
    glm::vec3 position;
};

#endif // MINECRAFT_LEYVEI_EDITION_BLOCK_H
