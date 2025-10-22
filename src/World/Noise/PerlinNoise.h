#ifndef MINECRAFT_PERLINNOISE_H
#define MINECRAFT_PERLINNOISE_H

#include <cstdint>
#include <vector>

class PerlinNoise {
public:
    // Constructeur avec graine aléatoire
    explicit PerlinNoise(uint32_t seed = 0);

    // Génère du bruit de Perlin 2D (pour le terrain)
    double noise(double x, double z) const;

    // Génère du bruit de Perlin 3D (pour les cavernes/structures)
    double noise(double x, double y, double z) const;

    // Génère du bruit avec plusieurs octaves (pour plus de détails)
    double octaveNoise(double x, double z, int octaves = 4, double persistence = 0.5) const;
    double octaveNoise(double x, double y, double z, int octaves = 4, double persistence = 0.5) const;

private:
    // Tableau de permutations (doublé pour éviter les modulo)
    int p[512];

    // Fonction de fading (courbe en S)
    static double fade(double t);

    // Interpolation linéaire
    static double lerp(double t, double a, double b);

    // Calcul du produit scalaire entre le gradient et le vecteur distance
    static double grad(int hash, double x, double y, double z);

    // Initialise le tableau de permutations avec la graine
    void initPermutations(uint32_t seed);
};

#endif //MINECRAFT_PERLINNOISE_H
