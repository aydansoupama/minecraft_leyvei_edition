//
// Created by leyve on 21/10/2025.
//

#ifndef MINECRAFT_LEYVEI_EDITION_GAME_H
#define MINECRAFT_LEYVEI_EDITION_GAME_H

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Shader/Shader.h"
#include "../Block/Block.h"

class Game {
public:
    Game(int width, int height, const char* title);
    ~Game();

    void run();

private:
    int width;
    int height;
    const char* title;

    GLFWwindow* window = nullptr;
    Shader* shader = nullptr;
    Block* block = nullptr;

    void processInput();
    void update();
    void render();
};

#endif //MINECRAFT_LEYVEI_EDITION_GAME_H
