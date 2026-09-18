#pragma once
#include <iostream>
#include <limits>

class GameEngine;
class AbstractState {
    public: 
        virtual ~AbstractState() = default;
        virtual void run(GameEngine& engine) = 0;
        int choice(int min, int max);
};