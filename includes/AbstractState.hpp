#pragma once
#include <iostream>
#include <limits>

class GameEngine;
/*
classe abstraite d'où sont hérité chaque état possible du jeu
*/
class AbstractState {
    public: 
        virtual ~AbstractState() = default;
        virtual void run(GameEngine& engine) = 0;
        int choice(int min, int max);
};