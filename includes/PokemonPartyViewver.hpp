#pragma once
#include "AbstractState.hpp"
#include "Button.hpp"
#include "Pokemon.hpp"
#include <memory>
#include <vector>

class GameEngine;

class PokemonPartyViewver : public AbstractState{
    private:
        std::vector<std::shared_ptr<Pokemon>> entries;
        std::vector<sf::Text> rowTexts;
        int currentPage = 0;
        static constexpr int rowsPerPage = 7;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Text titleText;
        sf::Text emptyText;
        sf::Text pageText;
        Button backButton;
        Button prevButton;
        Button nextButton;

        void rebuildPage(sf::Font& font);
        int pageCount() const;

    public :
        PokemonPartyViewver(GameEngine& engine);
        void handleEvent(const sf::Event& event, GameEngine& engine) override;
        void render(sf::RenderWindow& window) override;
};