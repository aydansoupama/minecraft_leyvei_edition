#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <array>
#include <memory>
#include "../../Block/Block.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Shader/Shader.h"
#include "../Noise/Noise.h"

// Forward declaration
class World;

class Chunk {
public:
    Chunk(int x, int y, int z);
    ~Chunk();

    void generate();
    void render(Shader* shader, World* world);

    Block* getBlock(int x, int y, int z);
    void setBlock(int x, int y, int z, std::shared_ptr<Block> block);

    void generateTerrain(Noise& noise);

    // Getters for chunk coordinates
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }

private:
    int x, y, z;
    std::array<std::array<std::array<std::shared_ptr<Block>, 16>, 16>, 16> blocks;
};

#endif // CHUNK_H
