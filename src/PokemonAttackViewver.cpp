#include "PokemonAttackViewver.hpp"
#include "GameEngine.hpp"
#include "Exploration.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"
#include <memory>
#include <sstream>
#include <algorithm>

std::string PokemonAttackViewver::rowLabel(const std::shared_ptr<Pokemon>& p) {
    std::ostringstream oss;
    oss << p->GetName() << "  (" << static_cast<int>(p->GetHitPoint())
        << "/" << static_cast<int>(p->GetHitPointMax()) << " PV)";
    return oss.str();
}

PokemonAttackViewver::PokemonAttackViewver(GameEngine& engine)
    : backButton("Retour a l'exploration", engine.getFont(), {362.f, 690.f}, {300.f, 60.f})
{
    if (!backgroundTexture.loadFromFile("data/BG.png")) {
        std::cout << "Erreur : Impossible de charger data/BG.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    titleText = UI::makeText("Mon equipe de combat", engine.getFont(), Theme::TitleSize, Theme::Accent);
    UI::centerOrigin(titleText);
    titleText.setPosition(Theme::WindowWidth / 2.f, 55.f);

    attackHeaderText = UI::makeText("Equipe actuelle (clic = retirer)", engine.getFont(), Theme::SubtitleSize, Theme::TextPrimary);
    attackHeaderText.setPosition(40.f, 115.f);

    availableHeaderText = UI::makeText("Ma collection (clic = ajouter)", engine.getFont(), Theme::SubtitleSize, Theme::TextPrimary);
    availableHeaderText.setPosition(544.f, 115.f);

    messageText = UI::makeText("", engine.getFont(), Theme::TextSize, Theme::Accent);

    emptyAttackText = UI::makeText("Aucun pokemon dans l'equipe.", engine.getFont(), Theme::TextSize, Theme::TextSecondary);
    emptyAttackText.setPosition(40.f, 170.f);

    emptyAvailableText = UI::makeText("Votre collection est vide.", engine.getFont(), Theme::TextSize, Theme::TextSecondary);
    emptyAvailableText.setPosition(544.f, 170.f);

    moreAvailableText = UI::makeText("", engine.getFont(), Theme::TextSize, Theme::TextSecondary);
    moreAvailableText.setPosition(544.f, 660.f);

    rebuildLists(engine);
}

void PokemonAttackViewver::rebuildLists(GameEngine& engine) {
    attackEntries.clear();
    for (auto& p : engine.getAttack()) {
        attackEntries.push_back(p);
    }

    availableEntries.clear();
    for (auto& p : engine.getParty()) {
        bool alreadyInTeam = false;
        for (auto& a : attackEntries) {
            if (a.get() == p.get()) { 
                alreadyInTeam = true; 
                break;
            }
        }
        if (!alreadyInTeam) {
            availableEntries.push_back(p);
        }
    }

    attackButtons.clear();
    for (size_t i = 0; i < attackEntries.size(); ++i) {
        attackButtons.emplace_back(rowLabel(attackEntries[i]), engine.getFont(),sf::Vector2f(40.f, 170.f + i * 60.f), sf::Vector2f(440.f, 50.f));
    }

    availableButtons.clear();
    size_t visibleCount = std::min(availableEntries.size(), static_cast<size_t>(MaxVisibleAvailable));
    for (size_t i = 0; i < visibleCount; ++i) {
        availableButtons.emplace_back(rowLabel(availableEntries[i]), engine.getFont(), sf::Vector2f(544.f, 170.f + i * 60.f), sf::Vector2f(440.f, 50.f));
    }

    if (availableEntries.size() > visibleCount) {
        std::ostringstream oss;
        oss << "+ " << (availableEntries.size() - visibleCount) << " autre(s) non affiche(s)";
        moreAvailableText.setString(oss.str());
    } else {
        moreAvailableText.setString("");
    }
}

void PokemonAttackViewver::setMessage(const std::string& message) {
    messageText.setString(message);
    UI::centerOrigin(messageText);
    messageText.setPosition(Theme::WindowWidth / 2.f, 630.f);
}

void PokemonAttackViewver::handleEvent(const sf::Event& event, GameEngine& engine) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(engine.getWindow()));

    if (backButton.isClicked(event, mousePos)) {
        engine.changeState(std::make_unique<Exploration>(engine));
        return;
    }

    for (size_t i = 0; i < attackButtons.size(); ++i) {
        if (attackButtons[i].isClicked(event, mousePos)) {
            setMessage(attackEntries[i]->GetName() + " a ete retire de l'equipe !");
            engine.getAttack().removePokemon(attackEntries[i]);
            rebuildLists(engine);
            return;
        }
    }

    for (size_t i = 0; i < availableButtons.size(); ++i) {
        if (availableButtons[i].isClicked(event, mousePos)) {
            if (engine.getAttack().size() >= MaxTeamSize) {
                setMessage("Equipe deja complete (6 pokemons maximum) !");
            } else {
                setMessage(availableEntries[i]->GetName() + " a rejoint l'equipe !");
                engine.getAttack().addPokemon(availableEntries[i]);
                rebuildLists(engine);
            }
            return;
        }
    }
}

void PokemonAttackViewver::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(attackHeaderText);
    window.draw(availableHeaderText);

    if (attackButtons.empty()) {
        window.draw(emptyAttackText);
    } else {
        for (auto& b : attackButtons) { 
            b.update(mousePos);
            b.draw(window);
        }
    }

    if (availableButtons.empty()) {
        window.draw(emptyAvailableText);
    } else {
        for (auto& b : availableButtons) { 
            b.update(mousePos); 
            b.draw(window);
        }
        window.draw(moreAvailableText);
    }

    window.draw(messageText);

    backButton.update(mousePos);
    backButton.draw(window);
}