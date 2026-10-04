#include "WildEncounterState.hpp"
#include "GameEngine.hpp"
#include "Exploration.hpp"
#include "GameOverState.hpp"
#include "Pokedex.hpp"
#include "BattleLayout.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"
#include <memory>
#include <sstream>

WildEncounterState::WildEncounterState(GameEngine& engine)
    : wildBox(engine.getFont(), BattleLayout::OpponentInfoPos),
      fighterBox(engine.getFont(), BattleLayout::PlayerInfoPos),
      attackButton("Attaquer", engine.getFont(), BattleLayout::buttonSlot(0), BattleLayout::ButtonSize),
      pokeballButton("Utiliser une Pokeball", engine.getFont(), BattleLayout::buttonSlot(1), BattleLayout::ButtonSize),
      fleeButton("Fuir", engine.getFont(), BattleLayout::buttonSlot(2), BattleLayout::ButtonSize),
      quitButton("Quitter le jeu", engine.getFont(), BattleLayout::buttonSlot(3), BattleLayout::ButtonSize),
      continueWithNextButton("Continuer le combat", engine.getFont(), BattleLayout::buttonSlot(0), BattleLayout::ButtonSize),
      fleeFightButton("Prendre la fuite", engine.getFont(), BattleLayout::buttonSlot(1), BattleLayout::ButtonSize),
      continueButton("Retourner explorer", engine.getFont(), BattleLayout::buttonSlot(0), BattleLayout::ButtonSize)
{
    if (!backgroundTexture.loadFromFile("data/BGbattle.png")) {
        std::cout << "Erreur : Impossible de charger data/BGbattle.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    wildPokemon = std::make_shared<Pokemon>(Pokedex::getPokedex().GetPokemon(int(engine.random())));

    for (auto& p : engine.getAttack()) {
        if (p->GetHitPoint() > 0) { 
            fighter = p; 
            break;
        }
    }

    titleText = UI::makeText("Rencontre sauvage", engine.getFont(), Theme::TitleSize, Theme::Accent);
    titleText.setOutlineThickness(3.f);                    // lisible meme sur le ciel clair du decor
    titleText.setOutlineColor(sf::Color(0, 0, 0, 170));
    UI::centerOrigin(titleText);
    titleText.setPosition(Theme::WindowWidth / 2.f, 40.f);

    logText = UI::makeText("", engine.getFont(), Theme::TextSize, Theme::TextPrimary);
    logText.setLineSpacing(1.3f);

    wildSprite.load(wildPokemon->GetID(), BattleLayout::OpponentFeet, BattleLayout::OpponentSpriteSize, false);
    refreshFighterSprite();
    refreshInfoBoxes();

    std::ostringstream introLog;
    introLog << "Vous rencontrez " << wildPokemon->GetName()
              << " (PV : " << static_cast<int>(wildPokemon->GetHitPoint())
              << "  ATQ : " << static_cast<int>(wildPokemon->GetAttack())
              << "  DEF : " << static_cast<int>(wildPokemon->GetDefense()) << ")";
    setLog(introLog.str());
}

void WildEncounterState::refreshInfoBoxes() {
    wildBox.setPokemon(wildPokemon->GetName(), wildPokemon->GetHitPoint(), wildPokemon->GetHitPointMax());

    if (fighter) {
        fighterBox.setPokemon(fighter->GetName(), fighter->GetHitPoint(), fighter->GetHitPointMax());
    } else {
        fighterBox.setMessage("Aucun pokemon disponible");
    }
}

// Charge l'image de notre pokemon sur sa plateforme (a appeler a chaque changement de combattant).
// Il regarde vers la droite, c'est-a-dire vers le pokemon sauvage (image retournee).
void WildEncounterState::refreshFighterSprite() {
    if (fighter) {
        fighterSprite.load(fighter->GetID(), BattleLayout::PlayerFeet, BattleLayout::PlayerSpriteSize, true);
    }
}

void WildEncounterState::setLog(const std::string& message) {
    logText.setString(UI::wrapText(message, *logText.getFont(), Theme::TextSize, BattleLayout::LogTextWidth));
    logText.setPosition(BattleLayout::LogTextPos);
}

void WildEncounterState::playRound(GameEngine& engine) {
    std::ostringstream log;

    int randint_attack = engine.random();
    if (randint_attack <= 15) {
        log << wildPokemon->GetName() << " a feinte l'attaque...\n";
    } else {
        fighter->isattacking(*wildPokemon);
        log << fighter->GetName() << " attaque " << wildPokemon->GetName() << " !\n";
    }

    int randint_defense = engine.random();
    if (randint_defense <= 15) {
        log << fighter->GetName() << " a feinte l'attaque...\n";
    } else {
        wildPokemon->isattacking(*fighter);
        log << wildPokemon->GetName() << " riposte !\n";
    }

    refreshInfoBoxes();

    if (wildPokemon->GetHitPoint() <= 0) {
        log << wildPokemon->GetName() << " a ete vaincu...";
        setLog(log.str());
        phase = Phase::Victory;
        return;
    }

    if (fighter->GetHitPoint() <= 0) {
        log << fighter->GetName() << " a ete vaincu...";
        std::shared_ptr<Pokemon> next = nullptr;
        for (auto& p : engine.getAttack()) {
            if (p->GetHitPoint() > 0) { next = p; break; }
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

void WildEncounterState::handleEvent(const sf::Event& event, GameEngine& engine) {
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
        else if (fleeButton.isClicked(event, mousePos)) {
            engine.changeState(std::make_unique<Exploration>(engine));
        }
        else if (pokeballButton.isClicked(event, mousePos)) {
            int randint = engine.random();
            if (randint <= 85) {
                engine.getParty().addPokemon(*wildPokemon);
                captured = true;
                setLog(wildPokemon->GetName() + " a ete capture !");
            } else {
                setLog(wildPokemon->GetName() + " s'est echappe...");
            }
            phase = Phase::CaptureResult;
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
        else if (fleeFightButton.isClicked(event, mousePos)) {
            engine.changeState(std::make_unique<Exploration>(engine));
        }
        return;
    }

    if ((phase == Phase::Victory || phase == Phase::CaptureResult) && continueButton.isClicked(event, mousePos)) {
        engine.changeState(std::make_unique<Exploration>(engine));
    }
}

void WildEncounterState::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    window.draw(backgroundSprite);
    window.draw(titleText);

    // Les pokemons sur leurs plateformes (un pokemon K.O. ou capture disparait).
    if (wildPokemon->GetHitPoint() > 0 && !captured) {
        wildSprite.draw(window);
    }
    if (fighter && fighter->GetHitPoint() > 0) {
        fighterSprite.draw(window);
    }

    wildBox.draw(window);
    fighterBox.draw(window);

    UI::drawPanel(window, BattleLayout::LogPanelPos, BattleLayout::LogPanelSize, Theme::PanelOverlay, Theme::Accent);
    window.draw(logText);

    if (phase == Phase::Intro) {
        attackButton.update(mousePos);
        attackButton.draw(window);
        fleeButton.update(mousePos);
        fleeButton.draw(window);
        pokeballButton.update(mousePos);
        pokeballButton.draw(window);
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
        fleeFightButton.update(mousePos);
        fleeFightButton.draw(window);
    }
    else if (phase == Phase::Victory || phase == Phase::CaptureResult) {
        continueButton.update(mousePos);
        continueButton.draw(window);
    }
}