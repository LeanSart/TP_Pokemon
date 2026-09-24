#pragma once
#include "AbstractState.hpp"
#include "Exploration.hpp"
#include "GameOverState.hpp"

/*
Etat de bataille contre un adversaire
*/
class BattleState : public AbstractState {
    public : 
        void run(GameEngine& engine) override;  
};