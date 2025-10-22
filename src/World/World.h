//
// Created by Cline on 21/10/2025.
//

#ifndef MINECRAFT_LEYVEI_EDITION_WORLD_H
#define MINECRAFT_LEYVEI_EDITION_WORLD_H

#pragma once
#include <vector>
#include <memory>
#include "../Block/Block.h"
#include "../Shader/Shader.h"
#include <glm/glm.hpp>
#include "Chunk/Chunk.h"

class World {
public:
    World();
    ~World();

    void generatePlatform();
    void generateChunks();
    void draw(Shader* shader);
    const std::vector<Block*>& getBlocks() const;

private:
    std::vector<Block*> blocks;
    std::vector<std::shared_ptr<Chunk>> chunks;
    int width = 16;
    int height = 16;
    int depth = 16;
};

#endif //MINECRAFT_LEYVEI_EDITION_WORLD_H
