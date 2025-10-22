#include "Chunk.h"
#include "../../Block/Block.h"
#include "../Noise/Noise.h"

Chunk::Chunk(int x, int y, int z) : x(x), y(y), z(z)
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
}

void Chunk::generateTerrain(Noise& noise) {
    // Generate terrain using noise functions with more variation
    for (int i = 0; i < 16; ++i) {
        for (int k = 0; k < 16; ++k) {
            // Calculate base height using noise
            float baseHeight = 4 + 4 * noise.generateSimplexNoise(
                (x * 16 + i) * 0.05f,
                0,
                (z * 16 + k) * 0.05f
            );

            // Add some randomness to the height
            float heightVariation = 2 * noise.generateSimplexNoise(
                (x * 16 + i) * 0.1f,
                1000,
                (z * 16 + k) * 0.1f
            );

            int surfaceHeight = static_cast<int>(baseHeight + heightVariation);

            // Clamp the surface height to reasonable values
            surfaceHeight = glm::clamp(surfaceHeight, 2, 15);

            for (int j = 0; j < 16; ++j) {
                if (j < surfaceHeight) {
                    // Below surface - dirt or stone
                    if (j < surfaceHeight - 2) {
                        // Deeper layers - more likely to be stone
                        float stoneChance = 0.3 + 0.7 * noise.generateSimplexNoise(
                            (x * 16 + i) * 0.2f,
                            j * 0.1f,
                            (z * 16 + k) * 0.2f
                        );
                        if (stoneChance > 0.5f) {
                            blocks[i][j][k] = std::make_shared<Block>(BlockType::STONE);
                        } else {
                            blocks[i][j][k] = std::make_shared<Block>(BlockType::DIRT);
                        }
                    } else {
                        // Surface layers - mostly dirt
                        blocks[i][j][k] = std::make_shared<Block>(BlockType::DIRT);
                    }
                } else if (j == surfaceHeight) {
                    // Surface layer - grass
                    blocks[i][j][k] = std::make_shared<Block>(BlockType::GRASS);
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
    // Clean up any dynamically allocated blocks
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
    Noise noise;

    // Generate terrain using noise functions
    generateTerrain(noise);
}

void Chunk::render(Shader *shader)
{
    // Render all blocks in the chunk
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            for (int k = 0; k < 16; ++k)
            {
                Block *block = blocks[i][j][k].get();
                if (block && block->getType() != BlockType::AIR)
                {
                    // Set block position based on chunk position and block position
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(
                                                      static_cast<float>(x * 16 + i),
                                                      static_cast<float>(j),
                                                      static_cast<float>(z * 16 + k)));

                    // Check if each face should be rendered
                    bool renderFront = true;
                    bool renderBack = true;
                    bool renderLeft = true;
                    bool renderRight = true;
                    bool renderTop = true;
                    bool renderBottom = true;

                    // FRONT (Z+)
                    if (k < 15 && blocks[i][j][k + 1] && blocks[i][j][k + 1]->getType() != BlockType::AIR)
                        renderFront = false;
                    else
                        renderFront = true;

                    // BACK (Z-)
                    if (k > 0 && blocks[i][j][k - 1] && blocks[i][j][k - 1]->getType() != BlockType::AIR)
                        renderBack = false;
                    else
                        renderBack = true;

                    // RIGHT (X+)
                    if (i < 15 && blocks[i + 1][j][k] && blocks[i + 1][j][k]->getType() != BlockType::AIR)
                        renderRight = false;
                    else
                        renderRight = true;

                    // LEFT (X-)
                    if (i > 0 && blocks[i - 1][j][k] && blocks[i - 1][j][k]->getType() != BlockType::AIR)
                        renderLeft = false;
                    else
                        renderLeft = true;

                    // TOP (Y+)
                    if (j < 15 && blocks[i][j + 1][k] && blocks[i][j + 1][k]->getType() != BlockType::AIR)
                        renderTop = false;
                    else
                        renderTop = true;

                    // BOTTOM (Y-)
                    if (j > 0 && blocks[i][j - 1][k] && blocks[i][j - 1][k]->getType() != BlockType::AIR)
                        renderBottom = false;
                    else
                        renderBottom = true;

                    // Render only visible faces
                    if (renderFront)
                    {
                        block->draw(shader, BlockFace::FRONT, glm::vec3(i, j, k));
                    }
                    if (renderBack)
                    {
                        block->draw(shader, BlockFace::BACK, glm::vec3(i, j, k));
                    }
                    if (renderLeft)
                    {
                        block->draw(shader, BlockFace::LEFT, glm::vec3(i, j, k));
                    }
                    if (renderRight)
                    {
                        block->draw(shader, BlockFace::RIGHT, glm::vec3(i, j, k));
                    }
                    if (renderTop)
                    {
                        block->draw(shader, BlockFace::TOP, glm::vec3(i, j, k));
                    }
                    if (renderBottom)
                    {
                        block->draw(shader, BlockFace::BOTTOM, glm::vec3(i, j, k));
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
    if (x >= 0 && x < 16 && y >= 0 && y < 16 && z >= 0 && z < 16)
    {
        blocks[x][y][z] = block;
    }
}
