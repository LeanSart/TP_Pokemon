#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/*
Cartouche d'information d'un pokemon en combat : un panneau semi-transparent
contenant son nom, sa barre de vie et ses PV.
*/
class PokemonInfoBox {
    private:
        static constexpr float Padding = 16.f;

        sf::Vector2f position;
        sf::Text nameText;
        sf::Text hpText;
        double currentHP = 0.0;
        double maxHP = 0.0;
        bool showHP = false;

        void setName(const std::string& name);

    public:
        static constexpr float Width  = 354.f;
        static constexpr float Height = 84.f;

        PokemonInfoBox(sf::Font& font, sf::Vector2f position);

        void setPokemon(const std::string& name, double currentHP, double maxHP);
        void setMessage(const std::string& message);

        void draw(sf::RenderWindow& window);
};
