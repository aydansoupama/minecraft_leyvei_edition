#include "Noise.h"
#include <glm/glm.hpp>

Noise::Noise(uint32_t seed) : perlinNoise(seed) {
    // Initialisation avec la graine fournie
}

Noise::~Noise() {
    // Destructor
}

float Noise::generatePerlinNoise(float x, float y, float z) {
    // Génère du bruit de Perlin 3D avec notre implémentation
    return static_cast<float>(perlinNoise.noise(x, y, z));
}

float Noise::generatePerlinOctaves(float x, float y, float z, int octaves, float persistence) {
    // Génère du bruit de Perlin 3D avec plusieurs octaves
    return static_cast<float>(perlinNoise.octaveNoise(x, y, z, octaves, static_cast<double>(persistence)));
}
