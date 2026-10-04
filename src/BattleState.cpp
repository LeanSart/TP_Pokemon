#include "BattleState.hpp"
#include "GameEngine.hpp"
#include "Exploration.hpp"
#include "GameOverState.hpp"
#include "Pokedex.hpp"
#include "BattleLayout.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"
#include <memory>
#include <sstream>

BattleState::BattleState(GameEngine& engine)
    : opponentBox(engine.getFont(), BattleLayout::OpponentInfoPos),
      fighterBox(engine.getFont(), BattleLayout::PlayerInfoPos),
      attackButton("Attaquer", engine.getFont(), BattleLayout::buttonSlot(0), BattleLayout::ButtonSize),
      quitButton("Quitter le jeu", engine.getFont(), BattleLayout::buttonSlot(1), BattleLayout::ButtonSize),
      continueWithNextButton("Continuer le combat", engine.getFont(), BattleLayout::buttonSlot(0), BattleLayout::ButtonSize),
      fleeButton("Prendre la fuite", engine.getFont(), BattleLayout::buttonSlot(1), BattleLayout::ButtonSize),
      victoryContinueButton("Retourner explorer", engine.getFont(), BattleLayout::buttonSlot(0), BattleLayout::ButtonSize)
{
    if (!backgroundTexture.loadFromFile("data/BGbattle.png")) {
        std::cout << "Erreur : Impossible de charger data/BGbattle.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    opponent = std::make_shared<Pokemon>(Pokedex::getPokedex().GetPokemon(int(engine.random())));

    for (auto& p : engine.getAttack()) {
        if (p->GetHitPoint() > 0) {
            fighter = p;
            break;
        }
    }

    titleText = UI::makeText("Combat contre Red", engine.getFont(), Theme::TitleSize, Theme::Accent);
    titleText.setOutlineThickness(3.f);                    // lisible meme sur le ciel clair du decor
    titleText.setOutlineColor(sf::Color(0, 0, 0, 170));
    UI::centerOrigin(titleText);
    titleText.setPosition(Theme::WindowWidth / 2.f, 40.f);

    logText = UI::makeText("", engine.getFont(), Theme::TextSize, Theme::TextPrimary);
    logText.setLineSpacing(1.3f);

    opponentSprite.load(opponent->GetID(), BattleLayout::OpponentFeet, BattleLayout::OpponentSpriteSize, false);
    refreshFighterSprite();
    refreshInfoBoxes();

    std::ostringstream introLog;
    introLog << "Vous rencontrez Red avec " << opponent->GetName()
              << " (PV : " << static_cast<int>(opponent->GetHitPoint())
              << "  ATQ : " << static_cast<int>(opponent->GetAttack())
              << "  DEF : " << static_cast<int>(opponent->GetDefense()) << ")";
    setLog(introLog.str());
}

void BattleState::refreshInfoBoxes() {
    opponentBox.setPokemon(opponent->GetName(), opponent->GetHitPoint(), opponent->GetHitPointMax());

    if (fighter) {
        fighterBox.setPokemon(fighter->GetName(), fighter->GetHitPoint(), fighter->GetHitPointMax());
    } else {
        fighterBox.setMessage("Aucun pokemon disponible");
    }
}

void BattleState::refreshFighterSprite() {
    if (fighter) {
        fighterSprite.load(fighter->GetID(), BattleLayout::PlayerFeet, BattleLayout::PlayerSpriteSize, true);
    }
}

void BattleState::setLog(const std::string& message) {
    logText.setString(UI::wrapText(message, *logText.getFont(), Theme::TextSize, BattleLayout::LogTextWidth));
    logText.setPosition(BattleLayout::LogTextPos);
}

void BattleState::playRound(GameEngine& engine) {
    std::ostringstream log;
    int randint_attack = engine.random();
    if (randint_attack <= 15) {
        log << opponent->GetName() << " a feinte l'attaque...\n";
    } else {
        fighter->isattacking(*opponent);
        log << fighter->GetName() << " attaque " << opponent->GetName() << " !\n";
    }

    int randint_defense = engine.random();
    if (randint_defense <= 15) {
        log << fighter->GetName() << " a feinte l'attaque...\n";
    } else {
        opponent->isattacking(*fighter);
        log << opponent->GetName() << " riposte !\n";
    }

    refreshInfoBoxes();

    if (opponent->GetHitPoint() <= 0) {
        log << opponent->GetName() << " a ete vaincu !";
        setLog(log.str());
        phase = Phase::Victory;
        return;
    }

    if (fighter->GetHitPoint() <= 0) {
        log << fighter->GetName() << " a ete vaincu...";
        std::shared_ptr<Pokemon> next = nullptr;
        for (auto& p : engine.getAttack()) {
            if (p->GetHitPoint() > 0) { 
                next = p; 
                break;
            }
        }
        if (next == nullptr) {
            setLog(log.str());
            engine.changeState(std::make_unique<GameOverState>(engine));
            return;
        }
        nextFighter = next;
        continueWithNextButton.setText("Continuer avec " + next->GetName());
        phase = Phase::ChooseNextFighter;
        setLog(log.str());
        return;
    }

    setLog(log.str());
}

void BattleState::handleEvent(const sf::Event& event, GameEngine& engine) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(engine.getWindow()));

    if (phase == Phase::Intro) {
        if (attackButton.isClicked(event, mousePos)) {
            if (fighter == nullptr) {
                engine.changeState(std::make_unique<GameOverState>(engine));
                return;
            }
            phase = Phase::Fighting;
            setLog("En avant, " + fighter->GetName() + " !");
        }
        else if (quitButton.isClicked(event, mousePos)) {
            engine.quit();
        }
        return;
    }

    if (phase == Phase::Fighting) {
        if (attackButton.isClicked(event, mousePos)) {
            playRound(engine);
        }
        return;
    }

    if (phase == Phase::ChooseNextFighter) {
        if (continueWithNextButton.isClicked(event, mousePos)) {
            fighter = nextFighter;
            nextFighter = nullptr;
            refreshFighterSprite();
            refreshInfoBoxes();
            phase = Phase::Fighting;
            setLog("En avant, " + fighter->GetName() + " !");
        }
        else if (fleeButton.isClicked(event, mousePos)) {
            engine.changeState(std::make_unique<Exploration>(engine));
        }
        return;
    }

    if (phase == Phase::Victory) {
        if (victoryContinueButton.isClicked(event, mousePos)) {
            engine.changeState(std::make_unique<Exploration>(engine));
        }
    }
}

void BattleState::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    window.draw(backgroundSprite);
    window.draw(titleText);


    if (opponent->GetHitPoint() > 0) {
        opponentSprite.draw(window);
    }
    if (fighter && fighter->GetHitPoint() > 0) {
        fighterSprite.draw(window);
    }

    opponentBox.draw(window);
    fighterBox.draw(window);

    UI::drawPanel(window, BattleLayout::LogPanelPos, BattleLayout::LogPanelSize, Theme::PanelOverlay, Theme::Accent);
    window.draw(logText);

    if (phase == Phase::Intro) {
        attackButton.update(mousePos); 
        attackButton.draw(window);
        quitButton.update(mousePos);
        quitButton.draw(window);
    }
    else if (phase == Phase::Fighting) {
        attackButton.update(mousePos);
        attackButton.draw(window);
    }
    else if (phase == Phase::ChooseNextFighter) {
        continueWithNextButton.update(mousePos); 
        continueWithNextButton.draw(window);
        fleeButton.update(mousePos);
        fleeButton.draw(window);
    }
    else if (phase == Phase::Victory) {
        victoryContinueButton.update(mousePos);
        victoryContinueButton.draw(window);
    }
}