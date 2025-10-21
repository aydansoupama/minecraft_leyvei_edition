#include "Block.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float Block::vertices[36 * 3];
const float Block::texCoords[36 * 2];

Block::Block(BlockType type, glm::vec3 pos)
    : position(pos)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(texCoords), nullptr, GL_STATIC_DRAW);

    // Load vertices data
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    // Load texture coordinates data
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(texCoords), texCoords);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)(sizeof(vertices)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Load texture based on block type
    switch (type)
    {
    case BlockType::GRASS:
    {
        topTexture = new Texture("assets/textures/block/grass_block_top.png");
        sideTexture = new Texture("assets/textures/block/grass_block_side_better.png");
        bottomTexture = new Texture("assets/textures/block/dirt.png");
        colorMap = new Texture("assets/textures/colormap/grass.png");
        break;
    }
    case BlockType::DIRT:
        topTexture = new Texture("assets/textures/block/dirt.png");
        sideTexture = new Texture("assets/textures/block/dirt.png");
        bottomTexture = new Texture("assets/textures/block/dirt.png");
        break;
    case BlockType::STONE:
    {
        int variant = rand() % 7 + 1;
        std::string stoneTexturePath = "assets/textures/block/stone" + std::to_string(variant) + ".png";
        topTexture = new Texture(stoneTexturePath.c_str());
        sideTexture = new Texture(stoneTexturePath.c_str());
        bottomTexture = new Texture(stoneTexturePath.c_str());
        break;
    }
    }
}

Block::~Block()
{
    delete topTexture;
    delete sideTexture;
    delete bottomTexture;
    if (colorMap) {
        delete colorMap;
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Block::draw(Shader *shader)
{
    glBindVertexArray(VAO);

    // Top face
    topTexture->bind(GL_TEXTURE0);
    if (colorMap) {
        colorMap->bind(GL_TEXTURE1);
        shader->use();
        shader->setBool("isTopFace", true);
    }
    glDrawArrays(GL_TRIANGLES, 30, 6);

    // Bottom face
    bottomTexture->bind(GL_TEXTURE0);
    shader->use();
    shader->setBool("isTopFace", false);
    glDrawArrays(GL_TRIANGLES, 24, 6);

    // Side faces (Front, Back, Left, Right)
    sideTexture->bind(GL_TEXTURE0);
    shader->use();
    shader->setBool("isTopFace", false);
    glDrawArrays(GL_TRIANGLES, 0, 24);

    glBindVertexArray(0);
}

const glm::vec3 &Block::getPosition() const
{
    return position;
}
