#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(int w, int h, const char *t) : width(w), height(h), title(t)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    // Mouse configuration for camera
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    block = new Block();
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // Initialization of interpolation variables
    previousCameraPosition = camera->Position;
    nextCameraPosition = camera->Position;
    lastTickTime = glfwGetTime();
    lastRenderTime = glfwGetTime();

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
}

Game::~Game()
{
    delete shader;
    delete block;
    delete camera;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::run()
{
    const double tickInterval = 1.0 / 20.0; // 20 ticks per second

    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTickTime = currentTime - lastTickTime;

        handleGameTick(deltaTickTime, tickInterval, currentTime);
        render();
        handleMouseInput();
        updateWindow();
    }
}

void Game::handleGameTick(double deltaTickTime, double tickInterval, double currentTime)
{
    // Update logic (keyboard movement) every 0.05 seconds (20 ticks/s)
    if (deltaTickTime >= tickInterval)
    {
        // Save current position as "previous"
        previousCameraPosition = camera->Position;

        // Update logic (movement, etc.)
        processInput(static_cast<float>(tickInterval));
        update();

        // Save new position as "next"
        nextCameraPosition = camera->Position;
        lastTickTime = currentTime;
    }
}

void Game::handleMouseInput()
{
    // Mouse handling (smooth, every frame)
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    static double lastX = xpos, lastY = ypos;
    static bool firstMouse = true;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    // Apply smooth deltaTime for mouse
    camera->processMouseMovement(xoffset, yoffset);
}

void Game::updateWindow()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::processInput(float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(0, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(1, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(2, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(3, deltaTime);
}

void Game::update()
{
    // Here you can add game logic (movement, terrain, etc.)
}

void Game::render()
{
    clearScreen();
    setupShader();
    setupCameraInterpolation();
    drawBlock();
    checkOpenGLErrors();
}

void Game::clearScreen()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::setupShader()
{
    shader->use();
    shader->setVec3("blockColor", glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::setupCameraInterpolation()
{
    // Camera position interpolation for smooth movement
    double alpha = (glfwGetTime() - lastTickTime) / (1.0 / 20.0);
    if (alpha > 1.0) alpha = 1.0;
    glm::vec3 interpolatedPosition = previousCameraPosition + static_cast<float>(alpha) * (nextCameraPosition - previousCameraPosition);

    // Create a temporary camera with interpolated position
    Camera tempCamera = *camera;
    tempCamera.Position = interpolatedPosition;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = tempCamera.getViewMatrix();
    glm::mat4 projection = tempCamera.getProjectionMatrix((float)width / (float)height);

    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
}

void Game::drawBlock()
{
    block->draw();
}

void Game::checkOpenGLErrors()
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
}
