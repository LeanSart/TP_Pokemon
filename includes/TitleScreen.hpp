#pragma once

#include "AbstractState.hpp"
#include "Pokemon.hpp"
#include "Pokedex.hpp"
#include "Button.hpp"
#include "PokemonSprite.hpp"

class GameEngine;
/*
Ecran titre : message de bienvenue, puis choix du pokemon de depart
parmi trois starters avant de demarrer l'exploration.
*/
class TitleScreen : public AbstractState{
    private : 
        enum class Phase { Welcome, ChooseStarter, Confirmation };
        Phase phase = Phase::Welcome;

        Pokemon starter1;
        Pokemon starter2;
        Pokemon starter3;
        Pokemon* chosenStarter = nullptr;

        PokemonSprite starterSprite1;
        PokemonSprite starterSprite2;
        PokemonSprite starterSprite3;

        sf::Texture backgroundTexture1;
        sf::Sprite backgroundSprite1;
        sf::Texture backgroundTexture2;
        sf::Sprite backgroundSprite2;
        sf::Texture backgroundTexture3;
        sf::Sprite backgroundSprite3;

        sf::Text subtitleText;
        sf::Text stat1Text;
        sf::Text stat2Text;
        sf::Text stat3Text;

        Button startButton;
        Button starter1Button;
        Button starter2Button;
        Button starter3Button;
        Button confirmButton;

        std::string DisplayStats(Pokemon& p);
        void refreshMessage(GameEngine& engine);
        
    public :
        TitleScreen(GameEngine& engine);
        void handleEvent(const sf::Event& event, GameEngine& engine) override;
        void render(sf::RenderWindow& window) override;
};