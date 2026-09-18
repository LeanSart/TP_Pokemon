#include "GameEngine.hpp"
#include "TitleScreen.hpp"

void GameEngine::run(){
    currentState = std::make_unique<TitleScreen>();

    while (running && currentState){
        currentState->run(*this);
    }
}
void GameEngine::changeState(std::unique_ptr<AbstractState> newState){
    currentState = std::move(newState);
}

void GameEngine::quit(){
    running = false;
}

PokemonParty& GameEngine::getParty(){
    return party;
}