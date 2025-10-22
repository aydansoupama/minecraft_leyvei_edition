#ifndef NOISE_H
#define NOISE_H

#include <glm/glm.hpp>
#include "FastNoiseLite.h"

class Noise {
public:
    Noise();
    ~Noise();

    float generatePerlinNoise(float x, float y, float z);
    float generateSimplexNoise(float x, float y, float z);

private:
    FastNoiseLite noiseGenerator;
};

#endif // NOISE_H
