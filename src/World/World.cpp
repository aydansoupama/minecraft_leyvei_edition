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
            blocks.push_back(new Block(BlockType::GRASS, glm::vec3(x, 0, z)));
        }
    }
}

void World::draw() {
    for (Block* block : blocks) {
        block->draw();
    }
}

const std::vector<Block*>& World::getBlocks() const {
    return blocks;
}