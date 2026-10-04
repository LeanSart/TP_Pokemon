#pragma once
#include "AbstractState.hpp"
#include "Button.hpp"
#include "Pokemon.hpp"
#include "PokemonInfoBox.hpp"
#include "PokemonSprite.hpp"
#include <memory>
#include <string>

class GameEngine;
/*
Etat de bataille contre un adversaire
*/
class BattleState : public AbstractState {
    private:
        enum class Phase { Intro, Fighting, ChooseNextFighter, Victory };
        Phase phase = Phase::Intro;

        std::shared_ptr<Pokemon> opponent;
        std::shared_ptr<Pokemon> fighter;
        std::shared_ptr<Pokemon> nextFighter;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Text titleText;
        sf::Text logText;

        PokemonInfoBox opponentBox;
        PokemonInfoBox fighterBox;
        PokemonSprite opponentSprite;
        PokemonSprite fighterSprite;

        Button attackButton;
        Button quitButton;
        Button continueWithNextButton;
        Button fleeButton;
        Button victoryContinueButton;

        void playRound(GameEngine& engine);
        void refreshInfoBoxes();
        void refreshFighterSprite();
        void setLog(const std::string& message);

    public :
        BattleState(GameEngine& engine);
        void handleEvent(const sf::Event& event, GameEngine& engine) override;
        void render(sf::RenderWindow& window) override;
};
