cmake_minimum_required(VERSION 4.0)
project(minecraft_leyvei_edition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Includes
include_directories(include external)

# GLAD
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include)

# GLM
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_SOURCE_DIR}/external)

# Executable
add_executable(minecraft_leyvei_edition
    src/main.cpp
    src/Game/Game.cpp
    src/Game/Game.h
    src/Block/Block.cpp
    src/Block/Block.h
    src/Shader/Shader.cpp
    src/Shader/Shader.h
    src/Camera/Camera.cpp
    src/Camera/Camera.h
)

# Link libraries
target_link_libraries(minecraft_leyvei_edition
    PRIVATE glad glm
    ${CMAKE_SOURCE_DIR}/lib/libglfw3.a
    -lopengl32 -lgdi32 -luser32 -lkernel32
)

# Copier les shaders dans le dossier de build
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
