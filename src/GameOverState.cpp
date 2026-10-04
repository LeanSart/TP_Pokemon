#include "GameOverState.hpp"
#include "GameEngine.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"
#include <iostream>

GameOverState::GameOverState(GameEngine& engine)
    : quitButton("Quitter", engine.getFont(), {362.f, 620.f}, {300.f, 60.f})
{
    if (!backgroundTexture.loadFromFile("data/GameOverBG.png")) {
        std::cout << "Erreur : Impossible de charger data/GameOverBG.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void GameOverState::handleEvent(const sf::Event& event, GameEngine& engine) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(engine.getWindow()));
    if (quitButton.isClicked(event, mousePos)) {
        engine.quit();
    }
}

void GameOverState::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    window.draw(backgroundSprite);
    quitButton.update(mousePos);
    quitButton.draw(window);
}