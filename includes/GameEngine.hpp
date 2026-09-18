#pragma once
#include <memory>
#include "AbstractState.hpp"
#include "PokemonParty.hpp"

class GameEngine{
private:
    std::unique_ptr<AbstractState> currentState;
    PokemonParty party;
    bool running = true;
public :
    void run();
    void changeState(std::unique_ptr<AbstractState> newState);
    void quit();
    PokemonParty& getParty();
};