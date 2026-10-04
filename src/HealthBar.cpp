#include "HealthBar.hpp"
#include "Theme.hpp"
#include <algorithm>

void HealthBar::draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size,
                      double currentHP, double maxHP) {
    double ratio = (maxHP > 0) ? std::clamp(currentHP / maxHP, 0.0, 1.0) : 0.0;

    sf::RectangleShape background(size);
    background.setPosition(position);
    background.setFillColor(sf::Color(20, 20, 28));
    background.setOutlineThickness(1.f);
    background.setOutlineColor(sf::Color(255, 255, 255, 60));
    window.draw(background);

    sf::Color fillColor = Theme::HPGreen;
    if (ratio <= 0.2) fillColor = Theme::HPRed;
    else if (ratio <= 0.5) fillColor = Theme::HPYellow;

    sf::RectangleShape fill(sf::Vector2f(size.x * static_cast<float>(ratio), size.y));
    fill.setPosition(position);
    fill.setFillColor(fillColor);
    window.draw(fill);
}
