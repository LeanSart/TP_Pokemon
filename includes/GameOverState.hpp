#pragma once

#include "AbstractState.hpp"
#include "Button.hpp"

class GameEngine;

/*
Ecran de fin de partie, affiche quand le joueur n'a plus de pokemon
en etat de se battre (ou quitte volontairement depuis un combat).
*/
class GameOverState : public AbstractState{
    private:
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        Button quitButton;

    public :
        GameOverState(GameEngine& engine);
        void handleEvent(const sf::Event& event, GameEngine& engine) override;
        void render(sf::RenderWindow& window) override;
};