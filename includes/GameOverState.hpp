#pragma once

#include "AbstractState.hpp"

class GameOverState : public AbstractState{
    public :
        void run(GameEngine& engine) override;
};