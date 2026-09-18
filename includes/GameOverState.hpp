#pragma once

#include "AbstractState.hpp"

class GameOverState : public AbstractState{
    public :
        void GameOverState::run(GameEngine& engine) override;
};