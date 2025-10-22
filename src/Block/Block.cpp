#include "Block.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include <iostream>

// Initialize static members
std::map<BlockType, Texture*> Block::textures;
bool Block::texturesLoaded = false;

Block::Block(BlockType type) : type(type), position(0.0f, 0.0f, 0.0f) {}

Block::~Block() {}

BlockType Block::getType() const {
    return type;
}

void Block::setType(BlockType type) {
    this->type = type;
}

void Block::loadTextures() {
    if (texturesLoaded) return;

    // Load textures for each block type
    textures[BlockType::STONE] = new Texture("assets/textures/block/stone.png");
    textures[BlockType::DIRT] = new Texture("assets/textures/block/dirt.png");
    textures[BlockType::GRASS] = new Texture("assets/textures/block/grass_block_top.png");

    texturesLoaded = true;
    std::cout << "Block textures loaded successfully!" << std::endl;
}

Texture* Block::getTextureForType(BlockType type) {
    if (!texturesLoaded) {
        loadTextures();
    }

    auto it = textures.find(type);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr; // No texture for this type
}

void Block::setupFaceVertices(BlockFace face, float* vertices, const glm::vec3& position) {
    // Define vertices for a single face with proper texture orientation
    // The texture coordinates are set to match Minecraft's standard orientation
    float x = position.x;
    float y = position.y;
    float z = position.z;

    switch(face) {
        case BlockFace::FRONT: // Z+
            vertices[0] = x - 0.5f; vertices[1] = y - 0.5f; vertices[2] = z + 0.5f; vertices[3] = 0.0f; vertices[4] = 0.0f;
            vertices[5] = x + 0.5f; vertices[6] = y - 0.5f; vertices[7] = z + 0.5f; vertices[8] = 1.0f; vertices[9] = 0.0f;
            vertices[10] = x + 0.5f; vertices[11] = y + 0.5f; vertices[12] = z + 0.5f; vertices[13] = 1.0f; vertices[14] = 1.0f;
            vertices[15] = x + 0.5f; vertices[16] = y + 0.5f; vertices[17] = z + 0.5f; vertices[18] = 1.0f; vertices[19] = 1.0f;
            vertices[20] = x - 0.5f; vertices[21] = y + 0.5f; vertices[22] = z + 0.5f; vertices[23] = 0.0f; vertices[24] = 1.0f;
            vertices[25] = x - 0.5f; vertices[26] = y - 0.5f; vertices[27] = z + 0.5f; vertices[28] = 0.0f; vertices[29] = 0.0f;
            break;
        case BlockFace::BACK: // Z-
            vertices[0] = x + 0.5f; vertices[1] = y - 0.5f; vertices[2] = z - 0.5f; vertices[3] = 0.0f; vertices[4] = 0.0f;
            vertices[5] = x - 0.5f; vertices[6] = y - 0.5f; vertices[7] = z - 0.5f; vertices[8] = 1.0f; vertices[9] = 0.0f;
            vertices[10] = x - 0.5f; vertices[11] = y + 0.5f; vertices[12] = z - 0.5f; vertices[13] = 1.0f; vertices[14] = 1.0f;
            vertices[15] = x - 0.5f; vertices[16] = y + 0.5f; vertices[17] = z - 0.5f; vertices[18] = 1.0f; vertices[19] = 1.0f;
            vertices[20] = x + 0.5f; vertices[21] = y + 0.5f; vertices[22] = z - 0.5f; vertices[23] = 0.0f; vertices[24] = 1.0f;
            vertices[25] = x + 0.5f; vertices[26] = y - 0.5f; vertices[27] = z - 0.5f; vertices[28] = 0.0f; vertices[29] = 0.0f;
            break;
        case BlockFace::RIGHT: // X+
            vertices[0] = x + 0.5f; vertices[1] = y - 0.5f; vertices[2] = z - 0.5f; vertices[3] = 0.0f; vertices[4] = 0.0f;
            vertices[5] = x + 0.5f; vertices[6] = y - 0.5f; vertices[7] = z + 0.5f; vertices[8] = 1.0f; vertices[9] = 0.0f;
            vertices[10] = x + 0.5f; vertices[11] = y + 0.5f; vertices[12] = z + 0.5f; vertices[13] = 1.0f; vertices[14] = 1.0f;
            vertices[15] = x + 0.5f; vertices[16] = y + 0.5f; vertices[17] = z + 0.5f; vertices[18] = 1.0f; vertices[19] = 1.0f;
            vertices[20] = x + 0.5f; vertices[21] = y + 0.5f; vertices[22] = z - 0.5f; vertices[23] = 0.0f; vertices[24] = 1.0f;
            vertices[25] = x + 0.5f; vertices[26] = y - 0.5f; vertices[27] = z - 0.5f; vertices[28] = 0.0f; vertices[29] = 0.0f;
            break;
        case BlockFace::LEFT: // X-
            vertices[0] = x - 0.5f; vertices[1] = y - 0.5f; vertices[2] = z + 0.5f; vertices[3] = 0.0f; vertices[4] = 0.0f;
            vertices[5] = x - 0.5f; vertices[6] = y - 0.5f; vertices[7] = z - 0.5f; vertices[8] = 1.0f; vertices[9] = 0.0f;
            vertices[10] = x - 0.5f; vertices[11] = y + 0.5f; vertices[12] = z - 0.5f; vertices[13] = 1.0f; vertices[14] = 1.0f;
            vertices[15] = x - 0.5f; vertices[16] = y + 0.5f; vertices[17] = z - 0.5f; vertices[18] = 1.0f; vertices[19] = 1.0f;
            vertices[20] = x - 0.5f; vertices[21] = y + 0.5f; vertices[22] = z + 0.5f; vertices[23] = 0.0f; vertices[24] = 1.0f;
            vertices[25] = x - 0.5f; vertices[26] = y - 0.5f; vertices[27] = z + 0.5f; vertices[28] = 0.0f; vertices[29] = 0.0f;
            break;
        case BlockFace::TOP: // Y+
            vertices[0] = x - 0.5f; vertices[1] = y + 0.5f; vertices[2] = z + 0.5f; vertices[3] = 0.0f; vertices[4] = 0.0f;
            vertices[5] = x + 0.5f; vertices[6] = y + 0.5f; vertices[7] = z + 0.5f; vertices[8] = 1.0f; vertices[9] = 0.0f;
            vertices[10] = x + 0.5f; vertices[11] = y + 0.5f; vertices[12] = z - 0.5f; vertices[13] = 1.0f; vertices[14] = 1.0f;
            vertices[15] = x + 0.5f; vertices[16] = y + 0.5f; vertices[17] = z - 0.5f; vertices[18] = 1.0f; vertices[19] = 1.0f;
            vertices[20] = x - 0.5f; vertices[21] = y + 0.5f; vertices[22] = z - 0.5f; vertices[23] = 0.0f; vertices[24] = 1.0f;
            vertices[25] = x - 0.5f; vertices[26] = y + 0.5f; vertices[27] = z + 0.5f; vertices[28] = 0.0f; vertices[29] = 0.0f;
            break;
        case BlockFace::BOTTOM: // Y-
            vertices[0] = x - 0.5f; vertices[1] = y - 0.5f; vertices[2] = z - 0.5f; vertices[3] = 0.0f; vertices[4] = 0.0f;
            vertices[5] = x + 0.5f; vertices[6] = y - 0.5f; vertices[7] = z - 0.5f; vertices[8] = 1.0f; vertices[9] = 0.0f;
            vertices[10] = x + 0.5f; vertices[11] = y - 0.5f; vertices[12] = z + 0.5f; vertices[13] = 1.0f; vertices[14] = 1.0f;
            vertices[15] = x + 0.5f; vertices[16] = y - 0.5f; vertices[17] = z + 0.5f; vertices[18] = 1.0f; vertices[19] = 1.0f;
            vertices[20] = x - 0.5f; vertices[21] = y - 0.5f; vertices[22] = z + 0.5f; vertices[23] = 0.0f; vertices[24] = 1.0f;
            vertices[25] = x - 0.5f; vertices[26] = y - 0.5f; vertices[27] = z - 0.5f; vertices[28] = 0.0f; vertices[29] = 0.0f;
            break;
    }
}

void Block::draw(Shader* shader, BlockFace face, const glm::vec3& blockPosition) {
    // Load textures if not already loaded
    if (!texturesLoaded) {
        loadTextures();
    }

    // Get texture for this block type
    Texture* texture = getTextureForType(type);
    if (!texture) return;

    // Setup vertices for this specific face
    float vertices[30]; // 6 vertices * 5 components each
    setupFaceVertices(face, vertices, blockPosition);

    // Create and configure VAO, VBO for this face
    static unsigned int VBO, VAO;
    static bool initialized = false;

    if (!initialized) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        initialized = true;
    }

    // Bind texture
    texture->bind(GL_TEXTURE0);
    shader->setInt("texture1", 0);

    // Configure VBO with face vertices
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw the face
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
