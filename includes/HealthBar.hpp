#pragma once
#include <SFML/Graphics.hpp>

/*
Barre de vie graphique : fond sombre + barre coloree proportionnelle aux
PV actuels. La couleur passe du vert au jaune puis au rouge selon le
pourcentage de vie restant.
*/
namespace HealthBar {
    void draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size,
              double currentHP, double maxHP);
}
