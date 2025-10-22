#ifndef NOISE_H
#define NOISE_H

#include <glm/glm.hpp>
#include "PerlinNoise.h"

class Noise {
public:
    Noise(uint32_t seed = 0);
    ~Noise();

    float generatePerlinNoise(float x, float y, float z);
    float generatePerlinOctaves(float x, float y, float z, int octaves = 4, float persistence = 0.5f);

private:
    PerlinNoise perlinNoise;
};

#endif // NOISE_H
