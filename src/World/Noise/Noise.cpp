#include "Noise.h"
#include <glm/glm.hpp>

Noise::Noise() {
    // Initialize FastNoiseLite with default settings
    noiseGenerator = FastNoiseLite(0); // Seed with 1337
}

Noise::~Noise() {
    // Destructor
}

float Noise::generatePerlinNoise(float x, float y, float z) {
    // Generate Perlin noise using FastNoiseLite
    return noiseGenerator.GetNoise(x, y, z);
}

float Noise::generateSimplexNoise(float x, float y, float z) {
    // Generate Simplex noise using FastNoiseLite
    return noiseGenerator.GetNoise(x, y, z);
}
