#pragma once
#include "AbstractState.hpp"
#include "Exploration.hpp"
#include "GameOverState.hpp"

/*
Etat de bataille contre un adversaire
*/
class BattleState : public AbstractState {
    public : 
        void BattleState::run(GameEngine& engine) override;  
};