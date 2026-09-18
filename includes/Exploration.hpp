#pragma once
#include "AbstractState.hpp"

class Exploration : public AbstractState {
    public : 
        void run(GameEngine& engine) override;
};