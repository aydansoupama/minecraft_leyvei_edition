#include "Chunk.h"
#include "../../Block/Block.h"

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
    // Generate a simple 16x16x16 chunk with some blocks
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            for (int k = 0; k < 16; ++k)
            {
                if (i == 0 || i == 15 || j == 0 || j == 15 || k == 0 || k == 15)
                {
                    // Set the outer layer to a specific block type
                    blocks[i][j][k] = std::make_shared<Block>(BlockType::STONE);
                }
                else if (j < 4)
                {
                    // Set the bottom 4 layers to dirt
                    blocks[i][j][k] = std::make_shared<Block>(BlockType::DIRT);
                }
                else if (j == 4)
                {
                    // Set the 5th layer to grass
                    blocks[i][j][k] = std::make_shared<Block>(BlockType::GRASS);
                }
                else
                {
                    // Set the rest to air
                    blocks[i][j][k] = std::make_shared<Block>(BlockType::AIR);
                }
            }
        }
    }
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
