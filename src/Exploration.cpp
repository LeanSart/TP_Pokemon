#include "Exploration.hpp"
#include "GameEngine.hpp"
#include "BattleState.hpp"
#include "WildEncounterState.hpp"
#include "PokemonPartyViewver.hpp"
#include "PokemonAttackViewver.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"

Exploration::Exploration(GameEngine& engine)
    : walkButton("Continuer a marcher", engine.getFont(), {362.f, 280.f}, {300.f, 60.f}),
      pokedexButton("Voir mon pokedex", engine.getFont(), {362.f, 360.f}, {300.f, 60.f}),
      teamButton("Voir mon equipe", engine.getFont(), {362.f, 440.f}, {300.f, 60.f}),
      quitButton("Quitter le jeu", engine.getFont(), {362.f, 520.f}, {300.f, 60.f})
{
    titleText = UI::makeText("Exploration", engine.getFont(), Theme::TitleSize, Theme::Accent);
    UI::centerOrigin(titleText);
    titleText.setPosition(Theme::WindowWidth / 2.f, 100.f);

    messageText = UI::makeText("Que voulez-vous faire ?", engine.getFont(), Theme::SubtitleSize, Theme::TextPrimary);
    UI::centerOrigin(messageText);
    messageText.setPosition(Theme::WindowWidth / 2.f, 180.f);

    if (!backgroundTexture.loadFromFile("data/BG.png")) {
        std::cout << "Erreur : Impossible de charger data/BG.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Exploration::handleEvent(const sf::Event& event, GameEngine& engine) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(engine.getWindow()));

    if (walkButton.isClicked(event, mousePos)) {
        int randint = engine.random();
        if (randint <= 30) {
            engine.changeState(std::make_unique<BattleState>(engine));
        }
        else if (randint <= 85) {
            engine.changeState(std::make_unique<WildEncounterState>(engine));
        }
        else {
            messageText.setString("Il n'y a pas grand chose par ici...");
            UI::centerOrigin(messageText);
            messageText.setPosition(Theme::WindowWidth / 2.f, 180.f);
        }
        return;
    }
    if (pokedexButton.isClicked(event, mousePos)) {
        engine.changeState(std::make_unique<PokemonPartyViewver>(engine));
        return;
    }
    if (teamButton.isClicked(event, mousePos)) {
        engine.changeState(std::make_unique<PokemonAttackViewver>(engine));
        return;
    }
    if (quitButton.isClicked(event, mousePos)) {
        engine.quit();
    }
}

void Exploration::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(messageText);

    walkButton.update(mousePos);
    pokedexButton.update(mousePos);
    teamButton.update(mousePos);
    quitButton.update(mousePos);

    walkButton.draw(window);
    pokedexButton.draw(window);
    teamButton.draw(window);
    quitButton.draw(window);
}
