#include "UIHelpers.hpp"
#include <sstream>

void UI::centerOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

sf::Text UI::makeText(const std::string& content, sf::Font& font, unsigned int size, const sf::Color& color) {
    sf::Text text;
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    return text;
}

void UI::drawPanel(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size,
                    const sf::Color& fill, const sf::Color& outline) {
    sf::RectangleShape panel(size);
    panel.setPosition(position);
    panel.setFillColor(fill);
    panel.setOutlineThickness(1.f);
    panel.setOutlineColor(outline);
    window.draw(panel);
}

std::string UI::wrapText(const std::string& content, const sf::Font& font, unsigned int size, float maxWidth) {
    sf::Text probe("", font, size);
    std::string result;
    std::istringstream paragraphs(content);
    std::string paragraph;
    bool firstParagraph = true;

    while (std::getline(paragraphs, paragraph, '\n')) {
        if (!firstParagraph) result += '\n';
        firstParagraph = false;

        std::istringstream words(paragraph);
        std::string word, line;
        while (std::getline(words, word, ' ')) {
            const std::string candidate = line.empty() ? word : line + " " + word;
            probe.setString(candidate);
            if (!line.empty() && probe.getLocalBounds().width > maxWidth) {
                result += line + '\n';
                line = word;
            } else {
                line = candidate;
            }
        }
        result += line;
    }
    return result;
}
