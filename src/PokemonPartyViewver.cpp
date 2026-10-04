#include "PokemonPartyViewver.hpp"
#include "GameEngine.hpp"
#include "Exploration.hpp"
#include "HealthBar.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"
#include <memory>
#include <sstream>
#include <algorithm>

PokemonPartyViewver::PokemonPartyViewver(GameEngine& engine)
    : backButton("Retour a l'exploration", engine.getFont(), {362.f, 660.f}, {300.f, 60.f}),
      prevButton("< Precedent", engine.getFont(), {162.f, 590.f}, {200.f, 50.f}),
      nextButton("Suivant >", engine.getFont(), {662.f, 590.f}, {200.f, 50.f})
{    
    if (!backgroundTexture.loadFromFile("data/BG.png")) {
        std::cout << "Erreur : Impossible de charger data/BG.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    for (auto& p : engine.getParty()) {
        entries.push_back(p);
    }

    titleText = UI::makeText("Mon Pokedex", engine.getFont(), Theme::TitleSize, Theme::Accent);
    UI::centerOrigin(titleText);
    titleText.setPosition(Theme::WindowWidth / 2.f, 70.f);

    emptyText = UI::makeText("Vous n'avez encore capture aucun pokemon.", engine.getFont(), Theme::SubtitleSize, Theme::TextSecondary);
    UI::centerOrigin(emptyText);
    emptyText.setPosition(Theme::WindowWidth / 2.f, 200.f);

    pageText = UI::makeText("", engine.getFont(), Theme::TextSize, Theme::TextSecondary);

    rebuildPage(engine.getFont());
}

int PokemonPartyViewver::pageCount() const {
    if (entries.empty()) return 1;
    return static_cast<int>((entries.size() + rowsPerPage - 1) / rowsPerPage);
}

void PokemonPartyViewver::rebuildPage(sf::Font& font) {
    rowTexts.clear();
    int start = currentPage * rowsPerPage;
    int end = std::min(static_cast<int>(entries.size()), start + rowsPerPage);
    float y = 150.f;
    for (int i = start; i < end; ++i) {
        sf::Text t = UI::makeText(entries[i]->GetName(), font, Theme::TextSize, Theme::TextPrimary);
        t.setPosition(112.f, y);
        rowTexts.push_back(t);
        y += 60.f;
    }

    std::ostringstream page;
    page << "Page " << (currentPage + 1) << " / " << pageCount();
    pageText.setString(page.str());
    UI::centerOrigin(pageText);
    pageText.setPosition(Theme::WindowWidth / 2.f, 615.f);
}

void PokemonPartyViewver::handleEvent(const sf::Event& event, GameEngine& engine) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(engine.getWindow()));

    if (backButton.isClicked(event, mousePos)) {
        engine.changeState(std::make_unique<Exploration>(engine));
        return;
    }
    if (pageCount() > 1) {
        if (prevButton.isClicked(event, mousePos) && currentPage > 0) {
            currentPage--;
            rebuildPage(engine.getFont());
        }
        else if (nextButton.isClicked(event, mousePos) && currentPage < pageCount() - 1) {
            currentPage++;
            rebuildPage(engine.getFont());
        }
    }
}

void PokemonPartyViewver::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    window.draw(backgroundSprite);
    window.draw(titleText);

    if (entries.empty()) {
        window.draw(emptyText);
    } else {
        int start = currentPage * rowsPerPage;
        for (size_t i = 0; i < rowTexts.size(); ++i) {
            window.draw(rowTexts[i]);
            const auto& p = entries[start + i];
            HealthBar::draw(window, {430.f, 150.f + i * 60.f + 6.f}, {380.f, 18.f}, p->GetHitPoint(), p->GetHitPointMax());
        }
        if (pageCount() > 1) {
            window.draw(pageText);
            prevButton.update(mousePos);
            prevButton.draw(window);
            nextButton.update(mousePos);
            nextButton.draw(window);
        }
    }

    backButton.update(mousePos);
    backButton.draw(window);
}