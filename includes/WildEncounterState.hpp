#pragma once
#include "AbstractState.hpp"
#include "Button.hpp"
#include "Pokemon.hpp"
#include "PokemonInfoBox.hpp"
#include "PokemonSprite.hpp"
#include <memory>
#include <string>

class GameEngine;

class WildEncounterState : public AbstractState {
    private:
        enum class Phase { Intro, Fighting, ChooseNextFighter, Victory, CaptureResult };
        Phase phase = Phase::Intro;
        bool captured = false;

        std::shared_ptr<Pokemon> wildPokemon;
        std::shared_ptr<Pokemon> fighter;
        std::shared_ptr<Pokemon> nextFighter;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Text titleText;
        sf::Text logText;

        PokemonInfoBox wildBox;
        PokemonInfoBox fighterBox;
        PokemonSprite wildSprite;
        PokemonSprite fighterSprite;

        Button attackButton;
        Button pokeballButton;
        Button fleeButton;
        Button quitButton;
        Button continueWithNextButton;
        Button fleeFightButton;
        Button continueButton;

        void playRound(GameEngine& engine);
        void refreshInfoBoxes();
        void refreshFighterSprite();
        void setLog(const std::string& message);

    public :
        WildEncounterState(GameEngine& engine);
        void handleEvent(const sf::Event& event, GameEngine& engine) override;
        void render(sf::RenderWindow& window) override;
};
