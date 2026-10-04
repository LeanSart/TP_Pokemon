#pragma once
#include <iostream>
#include <limits>
#include <SFML/Graphics.hpp>

class GameEngine;
/*
classe abstraite d'où sont hérité chaque état possible du jeu
*/
class AbstractState {
    public: 
        virtual ~AbstractState() = default;
        int choice(int min, int max);
        virtual void handleEvent(const sf::Event& event, GameEngine& engine) = 0;
        virtual void update(GameEngine& engine) { (void)engine; }
        virtual void render(sf::RenderWindow& window) = 0;
};