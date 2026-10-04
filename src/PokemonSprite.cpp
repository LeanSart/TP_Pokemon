#include "PokemonSprite.hpp"
#include <algorithm>
#include <iostream>
#include <string>

bool PokemonSprite::load(int id, sf::Vector2f feetPosition, float maxSize, bool mirrored) {
    visible = false;

    const std::string path = "data/pokemon/" + std::to_string(id) + ".png";
    sf::Image image;
    if (!image.loadFromFile(path)) {
        std::cout << "Erreur : Impossible de charger " << path << std::endl;
        return false;
    }

    // Boite englobante des pixels non transparents.
    const sf::Vector2u size = image.getSize();
    unsigned int minX = size.x, minY = size.y, maxX = 0, maxY = 0;
    for (unsigned int y = 0; y < size.y; ++y) {
        for (unsigned int x = 0; x < size.x; ++x) {
            if (image.getPixel(x, y).a > 0) {
                minX = std::min(minX, x);
                minY = std::min(minY, y);
                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);
            }
        }
    }
    if (minX > maxX || minY > maxY) {
        std::cout << "Erreur : " << path << " est entierement transparente" << std::endl;
        return false;
    }

    if (!texture.loadFromImage(image)) {
        std::cout << "Erreur : Impossible de creer la texture de " << path << std::endl;
        return false;
    }
    // Pixel art : pas de lissage (mettre true pour un rendu plus doux).
    texture.setSmooth(false);
    sprite.setTexture(texture, true);

    const float visibleWidth  = static_cast<float>(maxX - minX + 1);
    const float visibleHeight = static_cast<float>(maxY - minY + 1);
    const float scale = std::min(maxSize / std::max(visibleWidth, visibleHeight), MaxScale);

    // Origine = milieu du bas de la partie visible : c'est elle qu'on pose sur la plateforme.
    sprite.setOrigin(static_cast<float>(minX + maxX + 1) / 2.f, static_cast<float>(maxY + 1));
    sprite.setScale(mirrored ? -scale : scale, scale);
    sprite.setPosition(feetPosition);

    visible = true;
    return true;
}

void PokemonSprite::draw(sf::RenderWindow& window) const {
    if (visible) {
        window.draw(sprite);
    }
}
