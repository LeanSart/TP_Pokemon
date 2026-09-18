#pragma once
#include "GameEngine.hpp"
#include "Exploration.hpp"
#include "GameOverState.hpp"

class WildEncounterState : public AbstractState {
    public : 
        void WildEncounterState::run(GameEngine& engine) override;  
};