#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/*
Petites fonctions utilitaires pour construire des interfaces SFML,
reutilisees par tous les ecrans du jeu.
*/
namespace UI {
    // Centre l'origine d'un texte sur sa propre boite englobante, pour
    // pouvoir le positionner par son centre plutot que par son coin haut-gauche.
    void centerOrigin(sf::Text& text);

    // Construit un sf::Text pre-configure (police, taille, couleur).
    sf::Text makeText(const std::string& content, sf::Font& font, unsigned int size, const sf::Color& color);

    // Coupe un texte en lignes (ajoute des '\n') pour qu'aucune ligne ne depasse
    // maxWidth pixels. Les '\n' deja presents sont conserves.
    std::string wrapText(const std::string& content, const sf::Font& font, unsigned int size, float maxWidth);

    // Dessine un panneau rectangulaire avec bordure (fond de menu, carte...).
    void drawPanel(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size,
                   const sf::Color& fill, const sf::Color& outline = sf::Color(255, 255, 255, 40));
}
