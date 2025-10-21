# 🌍⛏️ Minecraft Leyvei Edition

[![C++](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![GLM](https://img.shields.io/badge/math-GLM-green.svg)](https://glm.g-truc.net/)
[![GLFW](https://img.shields.io/badge/window-GLFW-lightgrey.svg)](https://www.glfw.org/)
[![License](https://img.shields.io/badge/license-MIT-yellow.svg)](LICENSE)

**Un jeu sandbox inspiré de Minecraft développé en C++ avec OpenGL**

---

## 📖 À propos du projet

Minecraft Leyvei Edition est une implémentation personnalisée d'un moteur de jeu voxel inspiré de Minecraft, construit en C++ moderne et OpenGL. Ce projet démontre des techniques avancées de développement de jeux incluant :

- **Génération procédurale de monde** utilisant le bruit de Perlin
- **Rendu basé sur les chunks** pour des mondes infinis
- **Système de blocs personnalisé** avec texturage
- **Contrôles à la première personne** avec détection de collision
- **Rendu 3D OpenGL** avec shaders

---

## 🛠 Technologies utilisées

### Technologies principales
- **[C++17](https://isocpp.org/)** - Langage de programmation principal
- **[OpenGL 4.6](https://www.opengl.org/)** - Rendu graphique 3D
- **[GLM](https://glm.g-truc.net/)** - Bibliothèque mathématique pour OpenGL
- **[GLFW](https://www.glfw.org/)** - Gestion des fenêtres et des entrées
- **[GLAD](https://glad.dav1d.de/)** - Chargeur de fonctions OpenGL
- **[FastNoiseLite](https://github.com/Auburn/FastNoiseLite)** - Génération de bruit procédural

### Système de build
- **[CMake](https://cmake.org/)** - Configuration de build multiplateforme

---

## 🚀 Installation

### Prérequis

Assurez-vous d'avoir installé :
- Un compilateur compatible C++17 (GCC, Clang ou MSVC)
- CMake (version 3.10 ou supérieure)
- Git

### Étapes d'installation

1. **Cloner le dépôt**
   ```sh
   git clone https://github.com/aydansoupama/minecraft_leyvei_edition.git
   cd minecraft_leyvei_edition
   ```

2. **Créer un dossier de build**
   ```sh
   mkdir build && cd build
   ```

3. **Configurer avec CMake**
   ```sh
   cmake ..
   ```

4. **Builder le projet**
   ```sh
   cmake --build . --config Release
   ```

---

## 🎮 Utilisation

### Lancer le jeu
```sh
./minecraft_leyvei_edition
```

---

## 🤝 Contribution

Les contributions sont ce qui rend la communauté open source un endroit si incroyable pour apprendre, s'inspirer et créer. Toute contribution que vous apportez est **grandement appréciée**.

1. Fork le projet
2. Créez votre branche de fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. Commitez vos changements (`git commit -m 'Ajout d'une AmazingFeature'`)
4. Poussez vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrez une Pull Request

---

## 📄 Licence

Distribué sous la licence MIT. Voir `LICENSE` pour plus d'informations.

---

## 📧 Contact

Leyvei - [@leyvei](https://youtube.com/@leyvei) - leyvei.prodev@gmail.com

Lien du projet : [https://github.com/aydansoupama/minecraft_leyvei_edition](https://github.com/aydansoupama/minecraft_leyvei_edition)

---

## 🙏 Remerciements

- [Minecraft](https://www.minecraft.net/) pour l'inspiration
- La communauté [OpenGL](https://www.opengl.org/)
- Les développeurs de [GLM](https://glm.g-truc.net/)
- Tous les [contributeurs](https://github.com/aydansoupama/minecraft_leyvei_edition/graphs/contributors)

---
**© 2025 Minecraft Leyvei Edition. Tous droits réservés.**
