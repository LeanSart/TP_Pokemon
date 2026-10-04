#pragma once
#include "AbstractState.hpp"
#include "Button.hpp"
#include "Pokemon.hpp"
#include <memory>
#include <vector>
#include <string>

class GameEngine;

/*
Etat de visualisation et de modification de son équipe pour combattre
*/
class PokemonAttackViewver : public AbstractState {
    private:
        std::vector<std::shared_ptr<Pokemon>> attackEntries;
        std::vector<std::shared_ptr<Pokemon>> availableEntries;

        std::vector<Button> attackButtons;
        std::vector<Button> availableButtons;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Text titleText;
        sf::Text attackHeaderText;
        sf::Text availableHeaderText;
        sf::Text messageText;
        sf::Text emptyAttackText;
        sf::Text emptyAvailableText;
        sf::Text moreAvailableText;

        Button backButton;

        void rebuildLists(GameEngine& engine);
        void setMessage(const std::string& message);
        std::string rowLabel(const std::shared_ptr<Pokemon>& p);
        int MaxTeamSize = 6;
        int MaxVisibleAvailable = 8;
    public :
        PokemonAttackViewver(GameEngine& engine);
        void handleEvent(const sf::Event& event, GameEngine& engine) override;
        void render(sf::RenderWindow& window) override;
};