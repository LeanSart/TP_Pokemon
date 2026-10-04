#include "Button.hpp"
#include "UIHelpers.hpp"

Button::Button(const std::string& text, sf::Font& font, sf::Vector2f position, sf::Vector2f size,
               sf::Color normalColor, sf::Color hoverColor)
    : normalColor(normalColor), hoverColor(hoverColor)
{
    shape.setSize(size);
    shape.setFillColor(normalColor);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color(255, 255, 255, 60));

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(Theme::ButtonTextSize);
    label.setFillColor(Theme::TextPrimary);

    setPosition(position);
}

void Button::fitLabel() {
    label.setScale(1.f, 1.f);
    const float maxWidth = shape.getSize().x - 2.f * LabelPadding;
    const float width = label.getLocalBounds().width;
    if (width > maxWidth) {
        const float scale = maxWidth / width;
        label.setScale(scale, scale);
    }
}

void Button::setPosition(sf::Vector2f position) {
    shape.setPosition(position);
    fitLabel();
    UI::centerOrigin(label);
    label.setPosition(position.x + shape.getSize().x / 2.f, position.y + shape.getSize().y / 2.f);
}

void Button::setText(const std::string& text) {
    label.setString(text);
    setPosition(shape.getPosition());
}

void Button::setSelected(bool isSelected) {
    selected = isSelected;
    shape.setOutlineThickness(selected ? 3.f : 2.f);
    shape.setOutlineColor(selected ? Theme::ButtonSelected : sf::Color(255, 255, 255, 60));
}

void Button::update(sf::Vector2f mousePos) {
    hovered = shape.getGlobalBounds().contains(mousePos);
    shape.setFillColor(hovered ? hoverColor : normalColor);
}

bool Button::isClicked(const sf::Event& event, sf::Vector2f mousePos) const {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        return shape.getGlobalBounds().contains(mousePos);
    }
    return false;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

sf::FloatRect Button::getBounds() const {
    return shape.getGlobalBounds();
}
