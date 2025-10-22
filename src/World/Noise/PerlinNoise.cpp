#include "PerlinNoise.h"
#include <cmath>
#include <algorithm>
#include <random>

PerlinNoise::PerlinNoise(uint32_t seed) {
    initPermutations(seed);
}

// Fonction de fading (courbe en S pour adoucir les transitions)
double PerlinNoise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Interpolation linéaire
double PerlinNoise::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

// Calcul du produit scalaire entre le gradient et le vecteur distance
double PerlinNoise::grad(int hash, double x, double y, double z) {
    int h = hash & 15; // Convertir le hash en index de gradient (0-15)
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

// Génère du bruit de Perlin 2D
double PerlinNoise::noise(double x, double z) const {
    // Calcul des coordonnées de la cellule dans la grille
    int X = static_cast<int>(std::floor(x)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    // Calcul des coordonnées relatives dans la cellule
    x -= std::floor(x);
    z -= std::floor(z);

    // Calcul des coefficients de fading
    double u = fade(x);
    double v = fade(z);

    // Récupération des hash pour les 4 coins de la cellule
    int A = p[X] + Z;
    int B = p[X + 1] + Z;
    int AA = p[A];
    int AB = p[A + 1];
    int BA = p[B];
    int BB = p[B + 1];

    // Calcul des produits scalaires pour chaque coin
    double gradAA = grad(p[AA], x, 0, z);
    double gradBA = grad(p[BA], x - 1, 0, z);
    double gradAB = grad(p[AB], x, 0, z - 1);
    double gradBB = grad(p[BB], x - 1, 0, z - 1);

    // Interpolation linéaire sur X puis Z
    double x1 = lerp(u, gradAA, gradBA);
    double x2 = lerp(u, gradAB, gradBB);
    return (lerp(v, x1, x2) + 1.0) / 2.0; // Normalisation dans [0, 1]
}

// Génère du bruit de Perlin 3D
double PerlinNoise::noise(double x, double y, double z) const {
    // Calcul des coordonnées de la cellule dans la grille
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    // Calcul des coordonnées relatives dans la cellule
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    // Calcul des coefficients de fading
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    // Récupération des hash pour les 8 coins de la cellule
    int A = p[X] + Y;
    int B = p[X + 1] + Y;
    int AA = p[A] + Z;
    int AB = p[A] + Z + 1;
    int BA = p[B] + Z;
    int BB = p[B] + Z + 1;

    // Calcul des produits scalaires pour chaque coin
    double gradAAA = grad(p[AA], x, y, z);
    double gradBAA = grad(p[BA], x - 1, y, z);
    double gradABA = grad(p[AB], x, y - 1, z);
    double gradBBA = grad(p[BB], x - 1, y - 1, z);
    double gradAAB = grad(p[AA + 1], x, y, z - 1);
    double gradBAB = grad(p[BA + 1], x - 1, y, z - 1);
    double gradABB = grad(p[AB + 1], x, y - 1, z - 1);
    double gradBBB = grad(p[BB + 1], x - 1, y - 1, z - 1);

    // Interpolation linéaire sur X, Y puis Z
    double x1 = lerp(u, gradAAA, gradBAA);
    double x2 = lerp(u, gradABA, gradBBA);
    double y1 = lerp(v, x1, x2);

    double x3 = lerp(u, gradAAB, gradBAB);
    double x4 = lerp(u, gradABB, gradBBB);
    double y2 = lerp(v, x3, x4);

    return (lerp(w, y1, y2) + 1.0) / 2.0; // Normalisation dans [0, 1]
}

// Génère du bruit avec plusieurs octaves (pour plus de détails)
double PerlinNoise::octaveNoise(double x, double z, int octaves, double persistence) const {
    double total = 0.0;
    double frequency = 1.0;
    double amplitude = 1.0;
    double maxValue = 0.0;

    for (int i = 0; i < octaves; i++) {
        total += noise(x * frequency, z * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2.0;
    }

    return total / maxValue; // Normalisation
}

// Génère du bruit avec plusieurs octaves (version 3D)
double PerlinNoise::octaveNoise(double x, double y, double z, int octaves, double persistence) const {
    double total = 0.0;
    double frequency = 1.0;
    double amplitude = 1.0;
    double maxValue = 0.0;

    for (int i = 0; i < octaves; i++) {
        total += noise(x * frequency, y * frequency, z * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2.0;
    }

    return total / maxValue; // Normalisation
}

// Initialise le tableau de permutations avec la graine
void PerlinNoise::initPermutations(uint32_t seed) {
    // Initialisation du générateur aléatoire avec la graine
    std::mt19937 gen(seed);

    // Remplissage du tableau avec des valeurs de 0 à 255
    for (int i = 0; i < 256; i++) {
        p[i] = i;
    }

    // Mélange du tableau (algorithme de Fisher-Yates)
    for (int i = 255; i > 0; i--) {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        std::swap(p[i], p[j]);
    }

    // Duplication du tableau pour éviter les modulo
    for (int i = 0; i < 256; i++) {
        p[256 + i] = p[i];
    }
}
