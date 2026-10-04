#include "GameEngine.hpp"
#include "TitleScreen.hpp"
#include "Theme.hpp"
#include <iostream>

void GameEngine::run(){
    window.create(sf::VideoMode(Theme::WindowWidth, Theme::WindowHeight), "Pokemon : Edition ENSEA", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    if (!font.loadFromFile("data/fonts/font-pokemon.ttf")) {
        std::cerr << "Erreur : impossible de charger data/fonts/font-pokemon.ttf" << std::endl;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    try {
        currentState = std::make_unique<TitleScreen>(*this);
    } catch (const std::exception& e) {
    std::cerr << "Erreur fatale au demarrage : " << e.what() << std::endl;
    window.close();
    return;
    }
    while (running && currentState && window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                running = false;
                break;
            }
            if (currentState) {
                currentState->handleEvent(event, *this);
            }
        }
        if (currentState) {
            currentState->update(*this);
        }

        window.clear(Theme::Background);
        if (currentState) {
            currentState->render(window);
        }
        window.display();
    }
}
void GameEngine::changeState(std::unique_ptr<AbstractState> newState){
    currentState = std::move(newState);
}

void GameEngine::quit(){
    running = false;
    window.close();
}
int GameEngine::random(){
    std::uniform_int_distribution<int> distribution(1,100);
    return distribution(randomgenerator);
}

PokemonParty& GameEngine::getParty(){
    return party;
}

PokemonAttack& GameEngine::getAttack(){
    return attack;
}

sf::RenderWindow& GameEngine::getWindow(){
    return window;
}

sf::Font& GameEngine::getFont(){
    return font;
}