#include "TitleScreen.hpp"
#include "GameEngine.hpp"
#include "Exploration.hpp"
#include "BattleLayout.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"
#include <memory>
#include <sstream>

std::string TitleScreen::DisplayStats(Pokemon& p) {
    std::ostringstream oss;
    oss << "PV  : " << static_cast<int>(p.GetHitPoint()) << "\n"
        << "ATQ : " << static_cast<int>(p.GetAttack()) << "\n"
        << "DEF : " << static_cast<int>(p.GetDefense());
    return oss.str();
}

void TitleScreen::refreshMessage(GameEngine& engine) {
    std::string Message;
    switch (phase) {
        case Phase::Welcome:
            Message = "  ";
            break;
        case Phase::ChooseStarter:
            Message = "Choisissez votre premier partenaire :";
            break;
        case Phase::Confirmation:
            Message = "Felicitations ! \n Vous avez choisi " + (chosenStarter ? chosenStarter->GetName() : "") + " !";
            break;
    }
    subtitleText.setFont(engine.getFont());
    subtitleText.setString(Message);
    UI::centerOrigin(subtitleText);
    subtitleText.setPosition(Theme::WindowWidth / 2.f, 160.f);
}

TitleScreen::TitleScreen(GameEngine& engine)
    : starter1(Pokedex::getPokedex().GetPokemon("Bulbasaur")),
      starter2(Pokedex::getPokedex().GetPokemon("Charmander")),
      starter3(Pokedex::getPokedex().GetPokemon("Squirtle")),
      startButton("Commencer l'aventure", engine.getFont(), {362.f, 560.f}, {300.f, 60.f}),
    starter1Button(starter1.GetName(), engine.getFont(), {50.f, 660.f}, {260.f, 70.f}),
    starter2Button(starter2.GetName(), engine.getFont(), {390.f, 660.f}, {260.f, 70.f}),
    starter3Button(starter3.GetName(), engine.getFont(), {730.f, 660.f}, {260.f, 70.f}),
    confirmButton("Confirmer ce choix", engine.getFont(), {362.f, 380.f}, {300.f, 60.f})
{
    if (!backgroundTexture1.loadFromFile("data/TitleScreen.jpg")) {
        std::cout << "Erreur : Impossible de charger data/TitleScreen.jpg" << std::endl;
    }
    backgroundSprite1.setTexture(backgroundTexture1);
    if (!backgroundTexture2.loadFromFile("data/ChoosePokemon.png")) {
        std::cout << "Erreur : Impossible de charger data/ChoosePokemon.png" << std::endl;
    }
    backgroundSprite2.setTexture(backgroundTexture2);
    if (!backgroundTexture3.loadFromFile("data/BG.png")) {
        std::cout << "Erreur : Impossible de charger data/BG.png" << std::endl;
    }
    backgroundSprite3.setTexture(backgroundTexture3);

    sf::Vector2f spriteSize(150.f, 150.f);
    starterSprite1.load(starter1.GetID(), {180.f, 630.f}, BattleLayout::PlayerSpriteSize, false);
    starterSprite2.load(starter2.GetID(), {530.f, 630.f}, BattleLayout::PlayerSpriteSize, false);
    starterSprite3.load(starter3.GetID(), {850.f, 630.f}, BattleLayout::PlayerSpriteSize, false);

    stat1Text = UI::makeText(DisplayStats(starter1), engine.getFont(), Theme::TextSize, Theme::TextSecondary);
    stat2Text = UI::makeText(DisplayStats(starter2), engine.getFont(), Theme::TextSize, Theme::TextSecondary);
    stat3Text = UI::makeText(DisplayStats(starter3), engine.getFont(), Theme::TextSize, Theme::TextSecondary);
    stat1Text.setPosition(90.f, 260.f);
    stat2Text.setPosition(420.f, 260.f);
    stat3Text.setPosition(770.f, 260.f);
    refreshMessage(engine);
}

void TitleScreen::handleEvent(const sf::Event& event, GameEngine& engine) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(engine.getWindow()));

    if (phase == Phase::Welcome) {
        if (startButton.isClicked(event, mousePos)) {
            phase = Phase::ChooseStarter;
            refreshMessage(engine);
        }
        return;
    }

    if (phase == Phase::ChooseStarter) {
        if (starter1Button.isClicked(event, mousePos)) {
            chosenStarter = &starter1;
        }
        else if (starter2Button.isClicked(event, mousePos)) {
            chosenStarter = &starter2;
        }
        else if (starter3Button.isClicked(event, mousePos)) {
            chosenStarter = &starter3;
        }

        starter1Button.setSelected(chosenStarter == &starter1);
        starter2Button.setSelected(chosenStarter == &starter2);
        starter3Button.setSelected(chosenStarter == &starter3);

        if (chosenStarter != nullptr && confirmButton.isClicked(event, mousePos)) {
            engine.getParty().addPokemon(*chosenStarter);
            engine.getAttack().addPokemon(*chosenStarter);
            confirmButton.setText("Commencer l'exploration !");
            phase = Phase::Confirmation;
            refreshMessage(engine);
        }
        return;
    }

    if (phase == Phase::Confirmation) {
        if (confirmButton.isClicked(event, mousePos)) {
            engine.changeState(std::make_unique<Exploration>(engine));
        }
    }
}

void TitleScreen::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    
    if (phase == Phase::Welcome) {
        window.draw(backgroundSprite1);
        window.draw(subtitleText);
        startButton.update(mousePos);
        startButton.draw(window);
    }
    else if (phase == Phase::ChooseStarter) {
        window.draw(backgroundSprite2);
        window.draw(subtitleText);
        starterSprite1.draw(window);
        starterSprite2.draw(window);
        starterSprite3.draw(window);

        starter1Button.update(mousePos);
        starter2Button.update(mousePos);
        starter3Button.update(mousePos);
        
        starter1Button.draw(window);
        starter2Button.draw(window);
        starter3Button.draw(window);

        window.draw(stat1Text);
        window.draw(stat2Text);
        window.draw(stat3Text);

        if (chosenStarter != nullptr) {
            confirmButton.update(mousePos);
            confirmButton.draw(window);
        }
    }
    else if (phase == Phase::Confirmation) {
        window.draw(backgroundSprite3);
        window.draw(subtitleText);
        confirmButton.update(mousePos);
        confirmButton.draw(window);
    }
}