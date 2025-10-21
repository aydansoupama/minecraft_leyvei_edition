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
#include "../Camera/Camera.h"
#include "../World/World.h"

class Game
{
public:
    Game(int width, int height, const char *title);
    ~Game();

    void run();

private:
    int width;
    int height;
    const char *title;

    GLFWwindow *window = nullptr;
    Shader *shader = nullptr;
    World *world = nullptr;
    Camera *camera = nullptr;

    // Variables for camera interpolation
    glm::vec3 previousCameraPosition;
    glm::vec3 nextCameraPosition;
    double lastTickTime;
    double lastRenderTime;

    void processInput(float deltaTime);
    void update();
    void render();

    // Helper methods for game loop
    void handleGameTick(double deltaTickTime, double tickInterval, double currentTime);
    void handleMouseInput();
    void updateWindow();

    // Helper methods for rendering
    void clearScreen();
    void setupShader();
    void setupCameraInterpolation();
    void drawWorld();
    void checkOpenGLErrors();
};

#endif // MINECRAFT_LEYVEI_EDITION_GAME_H
