#include "PokemonInfoBox.hpp"
#include "HealthBar.hpp"
#include "Theme.hpp"
#include "UIHelpers.hpp"
#include <sstream>

PokemonInfoBox::PokemonInfoBox(sf::Font& font, sf::Vector2f position)
    : position(position)
{
    nameText = UI::makeText("", font, Theme::SubtitleSize, Theme::TextPrimary);
    hpText   = UI::makeText("", font, Theme::ButtonTextSize, Theme::TextSecondary);
}

void PokemonInfoBox::setName(const std::string& name) {
    nameText.setString(name);
    nameText.setScale(1.f, 1.f);
    const float maxWidth = Width - 2.f * Padding;
    const float width = nameText.getLocalBounds().width;
    if (width > maxWidth) {
        const float scale = maxWidth / width;
        nameText.setScale(scale, scale);
    }
    nameText.setPosition(position.x + Padding, position.y + 10.f);
}

void PokemonInfoBox::setPokemon(const std::string& name, double newCurrentHP, double newMaxHP) {
    currentHP = newCurrentHP;
    maxHP = newMaxHP;
    showHP = true;
    setName(name);

    std::ostringstream oss;
    oss << static_cast<int>(currentHP) << "/" << static_cast<int>(maxHP) << " PV";
    hpText.setString(oss.str());

    // Texte des PV aligne a droite, sous la barre de vie.
    const sf::FloatRect bounds = hpText.getLocalBounds();
    hpText.setPosition(position.x + Width - Padding - (bounds.left + bounds.width), position.y + 58.f);
}

void PokemonInfoBox::setMessage(const std::string& message) {
    showHP = false;
    setName(message);
}

void PokemonInfoBox::draw(sf::RenderWindow& window) {
    UI::drawPanel(window, position, {Width, Height}, Theme::PanelOverlay, Theme::Accent);
    window.draw(nameText);
    if (showHP) {
        HealthBar::draw(window, {position.x + Padding, position.y + 38.f}, {Width - 2.f * Padding, 16.f},
                        currentHP, maxHP);
        window.draw(hpText);
    }
}
