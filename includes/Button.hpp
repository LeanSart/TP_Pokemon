#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Theme.hpp"

/*
Bouton cliquable réutilisé dans tous les écrans du jeu
*/
class Button {
    private:
        sf::RectangleShape shape;
        sf::Text label;
        sf::Color normalColor;
        sf::Color hoverColor;
        bool hovered = false;
        bool selected = false;

        static constexpr float LabelPadding = 12.f;
        void fitLabel();   // reduit le texte s'il depasse du bouton

    public:
        Button(const std::string& text, sf::Font& font, sf::Vector2f position, sf::Vector2f size,
               sf::Color normalColor = Theme::ButtonNormal, sf::Color hoverColor = Theme::ButtonHover);

        void setPosition(sf::Vector2f position);
        void setText(const std::string& text);
        void setSelected(bool isSelected);

        // A appeler une fois par frame : met a jour l'effet de survol selon la position de la souris.
        void update(sf::Vector2f mousePos);

        // Vrai si le clic gauche vient d'etre relache au-dessus du bouton.
        bool isClicked(const sf::Event& event, sf::Vector2f mousePos) const;

        void draw(sf::RenderWindow& window);
        sf::FloatRect getBounds() const;
};
