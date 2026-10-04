#pragma once
#include "AbstractState.hpp"
#include "Button.hpp"

class GameEngine;
/*
Exploration : Etat d'exploration du jeu
*/
class Exploration : public AbstractState {
    private:
        Button walkButton;
        Button pokedexButton;
        Button teamButton;
        Button quitButton;

        sf::Text titleText;
        sf::Text messageText;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
    public :
        Exploration(GameEngine& engine);
        void handleEvent(const sf::Event& event, GameEngine& engine) override;
        void render(sf::RenderWindow& window) override;
};