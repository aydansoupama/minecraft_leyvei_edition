#include "World.h"
#include <iostream>

World::World() {}

World::~World()
{
    for (Block *block : blocks)
    {
        delete block;
    }
}

void World::generatePlatform()
{
    for (int x = 0; x < width; ++x)
    {
        for (int z = 0; z < depth; ++z)
        {
            blocks.push_back(new Block(BlockType::GRASS));
        }
    }
}

void World::generateChunks()
{
    for (int x_chunk = 0; x_chunk < 4; ++x_chunk)
    {
        for (int y_chunk = 0; y_chunk < 4; ++y_chunk)
        {
            chunks.push_back(std::make_shared<Chunk>(x_chunk, 0, y_chunk));
            chunks.back()->generate();
        }
    }
}

void World::draw(Shader *shader)
{
    // Draw all blocks in the old system
    for (Block *block : blocks)
    {
        // This is a placeholder - we need to implement proper block drawing
        // with face culling and texture mapping
    }

    // Draw all chunks
    for (auto &chunk : chunks)
    {
        chunk->render(shader, this);
    }
}

const std::vector<Block *> &World::getBlocks() const
{
    return blocks;
}

Block* World::getBlock(int globalX, int globalY, int globalZ) {
    // Assuming chunk size is 16x16x16
    int chunkX = globalX / 16;
    int chunkY = globalY / 16;
    int chunkZ = globalZ / 16;

    int localX = globalX % 16;
    int localY = globalY % 16;
    int localZ = globalZ % 16;

    // Handle negative coordinates for modulo correctly
    if (localX < 0) localX += 16;
    if (localY < 0) localY += 16;
    if (localZ < 0) localZ += 16;

    // Find the chunk
    for (auto& chunk : chunks) {
        // Use getter methods to access chunk coordinates
        if (chunk->getX() == chunkX && chunk->getY() == chunkY && chunk->getZ() == chunkZ) {
            return chunk->getBlock(localX, localY, localZ);
        }
    }
    return nullptr; // No chunk found at these coordinates
}
