#include "Chunk.h"
#include "../../Block/Block.h"
#include "../Noise/Noise.h"
#include "../../World/World.h"

Chunk::Chunk(int x, int y, int z) : x(x), y(y), z(z)
{
    // Initialize the 3D vector structure for blocks
    blocks.resize(CHUNK_SIZE_X);
    for (auto &layer : blocks)
    {
        layer.resize(CHUNK_SIZE_Y);
        for (auto &row : layer)
        {
            row.resize(CHUNK_SIZE_Z, nullptr);
        }
    }
}

void Chunk::generateTerrain(Noise& noise) {
    // Generate terrain using noise functions with more variation
    for (int i = 0; i < CHUNK_SIZE_X; ++i) {
        for (int k = 0; k < CHUNK_SIZE_Z; ++k) {
            // Calculate base height using noise
            float baseHeight = 64 + 32 * noise.generatePerlinOctaves(
                (x * CHUNK_SIZE_X + i) * 0.01f,
                0,
                (z * CHUNK_SIZE_Z + k) * 0.01f
            );

            // Add some randomness to the height
            float heightVariation = 16 * noise.generatePerlinOctaves(
                (x * CHUNK_SIZE_X + i) * 0.05f,
                1000,
                (z * CHUNK_SIZE_Z + k) * 0.05f
            );

            int surfaceHeight = static_cast<int>(baseHeight + heightVariation);

            // Clamp the surface height to reasonable values
            surfaceHeight = glm::clamp(surfaceHeight, 32, CHUNK_SIZE_Y - 1);

            for (int j = 0; j < CHUNK_SIZE_Y; ++j) {
                if (j < surfaceHeight) {
                    // Below surface - dirt or stone
                    if (j < surfaceHeight - 2) {
                        // Deeper layers - more likely to be stone
                        float stoneChance = 0.3 + 0.7 * noise.generatePerlinOctaves(
                            (x * 16 + i) * 0.2f,
                            j * 0.1f,
                            (z * 16 + k) * 0.2f
                        );
                        if (stoneChance > 0.5f) {
                            blocks[i][j][k] = std::make_shared<Block>(BlockType::STONE);
                        } else {
                            // blocks[i][j][k] = std::make_shared<Block>(BlockType::DIRT);
                            blocks[i][j][k] = std::make_shared<Block>(BlockType::STONE);
                        }
                    } else {
                        // Surface layers - mostly dirt
                        // blocks[i][j][k] = std::make_shared<Block>(BlockType::DIRT);
                        blocks[i][j][k] = std::make_shared<Block>(BlockType::STONE);
                    }
                } else if (j == surfaceHeight) {
                    // Surface layer - grass
                    // blocks[i][j][k] = std::make_shared<Block>(BlockType::GRASS);
                    blocks[i][j][k] = std::make_shared<Block>(BlockType::STONE);
                } else {
                    // Above surface - air
                    blocks[i][j][k] = std::make_shared<Block>(BlockType::AIR);
                }
            }
        }
    }
}

Chunk::~Chunk()
{
    for (auto &layer : blocks)
    {
        for (auto &row : layer)
        {
            for (auto &block : row)
            {
                if (block != nullptr)
                {
                    block.reset();
                }
            }
        }
    }
}

void Chunk::generate()
{
    // Initialize all blocks to nullptr
    for (auto &layer : blocks)
    {
        for (auto &row : layer)
        {
            for (auto &block : row)
            {
                block = nullptr;
            }
        }
    }

    // Create a Noise object for terrain generation
    Noise noise(1337); // Graine fixe pour la reproductibilité

    // Generate terrain using noise functions
    generateTerrain(noise);
}

void Chunk::render(Shader *shader, World* world)
{
    // Render all blocks in the chunk
    for (int i = 0; i < CHUNK_SIZE_X; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE_Y; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE_Z; ++k)
            {
                Block *block = blocks[i][j][k].get();
                if (block && block->getType() != BlockType::AIR)
                {
                    // Calculate the block's global model matrix
                    glm::mat4 blockModel = glm::mat4(1.0f);
                    blockModel = glm::translate(blockModel, glm::vec3(
                                                      static_cast<float>(x * 16 + i),
                                                      static_cast<float>(y * 16 + j),
                                                      static_cast<float>(z * 16 + k)));

                    shader->setMat4("model", blockModel);

                    // Check if each face should be rendered
                    bool renderFront = true;
                    bool renderBack = true;
                    bool renderLeft = true;
                    bool renderRight = true;
                    bool renderTop = true;
                    bool renderBottom = true;

                    // FRONT (Z+)
                    if (k == 15) { // At chunk boundary Z+
                        int neighborGlobalX = x * 16 + i;
                        int neighborGlobalY = y * 16 + j;
                        int neighborGlobalZ = z * 16 + k + 1;
                        if (world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ) &&
                            world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ)->getType() != BlockType::AIR) {
                            renderFront = false;
                        } else {
                            renderFront = true;
                        }
                    } else { // Inside chunk
                        if (blocks[i][j][k + 1] && blocks[i][j][k + 1]->getType() != BlockType::AIR)
                            renderFront = false;
                        else
                            renderFront = true;
                    }

                    // BACK (Z-)
                    if (k == 0) { // At chunk boundary Z-
                        int neighborGlobalX = x * 16 + i;
                        int neighborGlobalY = y * 16 + j;
                        int neighborGlobalZ = z * 16 + k - 1;
                        if (world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ) &&
                            world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ)->getType() != BlockType::AIR) {
                            renderBack = false;
                        } else {
                            renderBack = true;
                        }
                    }
                     else { // Inside chunk
                        if (blocks[i][j][k - 1] && blocks[i][j][k - 1]->getType() != BlockType::AIR)
                            renderBack = false;
                        else
                            renderBack = true;
                    }

                    // RIGHT (X+)
                    if (i == 15) { // At chunk boundary X+
                        int neighborGlobalX = x * 16 + i + 1;
                        int neighborGlobalY = y * 16 + j;
                        int neighborGlobalZ = z * 16 + k;
                        if (world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ) &&
                            world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ)->getType() != BlockType::AIR) {
                            renderRight = false;
                        } else {
                            renderRight = true;
                        }
                    } else { // Inside chunk
                        if (blocks[i + 1][j][k] && blocks[i + 1][j][k]->getType() != BlockType::AIR)
                            renderRight = false;
                        else
                            renderRight = true;
                    }

                    // LEFT (X-)
                    if (i == 0) { // At chunk boundary X-
                        int neighborGlobalX = x * 16 + i - 1;
                        int neighborGlobalY = y * 16 + j;
                        int neighborGlobalZ = z * 16 + k;
                        if (world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ) &&
                            world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ)->getType() != BlockType::AIR) {
                            renderLeft = false;
                        }
                         else {
                            renderLeft = true;
                        }
                    } else { // Inside chunk
                        if (blocks[i - 1][j][k] && blocks[i - 1][j][k]->getType() != BlockType::AIR)
                            renderLeft = false;
                        else
                            renderLeft = true;
                    }

                    // TOP (Y+)
                    if (j == 15) { // At chunk boundary Y+
                        int neighborGlobalX = x * 16 + i;
                        int neighborGlobalY = y * 16 + j + 1;
                        int neighborGlobalZ = z * 16 + k;
                        if (world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ) &&
                            world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ)->getType() != BlockType::AIR) {
                            renderTop = false;
                        }
                         else {
                            renderTop = true;
                        }
                    } else { // Inside chunk
                        if (blocks[i][j + 1][k] && blocks[i][j + 1][k]->getType() != BlockType::AIR)
                            renderTop = false;
                        else
                            renderTop = true;
                    }

                    // BOTTOM (Y-)
                    if (j == 0) { // At chunk boundary Y-
                        int neighborGlobalX = x * 16 + i;
                        int neighborGlobalY = y * 16 + j - 1;
                        int neighborGlobalZ = z * 16 + k;
                        if (world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ) &&
                            world->getBlock(neighborGlobalX, neighborGlobalY, neighborGlobalZ)->getType() != BlockType::AIR) {
                            renderBottom = false;
                        }
                         else {
                            renderBottom = true;
                        }
                    } else { // Inside chunk
                        if (blocks[i][j - 1][k] && blocks[i][j - 1][k]->getType() != BlockType::AIR)
                            renderBottom = false;
                        else
                            renderBottom = true;
                    }

                    // Render only visible faces
                    if (renderFront)
                    {
                        block->draw(shader, BlockFace::FRONT, glm::vec3(0.0f, 0.0f, 0.0f));
                    }
                    if (renderBack)
                    {
                        block->draw(shader, BlockFace::BACK, glm::vec3(0.0f, 0.0f, 0.0f));
                    }
                    if (renderLeft)
                    {
                        block->draw(shader, BlockFace::LEFT, glm::vec3(0.0f, 0.0f, 0.0f));
                    }
                    if (renderRight)
                    {
                        block->draw(shader, BlockFace::RIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
                    }
                    if (renderTop)
                    {
                        block->draw(shader, BlockFace::TOP, glm::vec3(0.0f, 0.0f, 0.0f));
                    }
                    if (renderBottom)
                    {
                        block->draw(shader, BlockFace::BOTTOM, glm::vec3(0.0f, 0.0f, 0.0f));
                    }
                }
            }
        }
    }
}

Block *Chunk::getBlock(int x, int y, int z)
{
    if (x >= 0 && x < 16 && y >= 0 && y < 16 && z >= 0 && z < 16)
    {
        return blocks[x][y][z].get();
    }
    return nullptr;
}

void Chunk::setBlock(int x, int y, int z, std::shared_ptr<Block> block)
{
    if (x >= 0 && x < CHUNK_SIZE_X && y >= 0 && y < CHUNK_SIZE_Y && z >= 0 && z < CHUNK_SIZE_Z)
    {
        blocks[x][y][z] = block;
    }
}
