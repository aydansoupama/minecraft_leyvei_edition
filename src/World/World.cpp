#include "World.h"
#include <iostream>

World::World() {}

World::~World() {
    for (Block* block : blocks) {
        delete block;
    }
}

void World::generatePlatform() {
    for (int x = 0; x < width; ++x) {
        for (int z = 0; z < depth; ++z) {
            blocks.push_back(new Block(BlockType::GRASS));
        }
    }
}

void World::generateChunks() {
    // Create a single chunk for demonstration
    chunks.push_back(std::make_shared<Chunk>(0, 0, 0));
    chunks.back()->generate();
}

void World::draw(Shader* shader) {
    // Draw all blocks in the old system
    for (Block* block : blocks) {
        // This is a placeholder - we need to implement proper block drawing
        // with face culling and texture mapping
    }

    // Draw all chunks
    for (auto& chunk : chunks) {
        chunk->render(shader);
    }
}

const std::vector<Block*>& World::getBlocks() const {
    return blocks;
}
