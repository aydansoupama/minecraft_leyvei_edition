#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <glad/glad.h>

class Shader;
class Texture;

enum class BlockFace {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

enum class BlockType {
    AIR,
    STONE,
    DIRT,
    GRASS,
    // Add more block types as needed
};

class Block {
public:
    Block(BlockType type);
    ~Block();

    BlockType getType() const;
    void setType(BlockType type);
    void draw(Shader* shader, BlockFace face, const glm::vec3& blockPosition);

private:
    BlockType type;
    glm::vec3 position;
    static std::map<BlockType, Texture*> textures;
    static bool texturesLoaded;

    static void loadTextures();
    static Texture* getTextureForType(BlockType type);
    static void setupFaceVertices(BlockFace face, float* vertices, const glm::vec3& position);
};
#endif // BLOCK_H
