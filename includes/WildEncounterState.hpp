#pragma once
#include "GameEngine.hpp"
#include "Exploration.hpp"
#include "GameOverState.hpp"

class WildEncounterState : public AbstractState {
    public : 
        void run(GameEngine& engine) override;  
};