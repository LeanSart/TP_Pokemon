#include "GameEngine.hpp"
#include "TitleScreen.hpp"

void GameEngine::run(){
    std::random_device rd;
    std::mt19937 gen(rd());
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
int GameEngine::random(){
    std::uniform_int_distribution<int> distribution(1,100);
    return distribution(randomgenerator);
}

PokemonParty& GameEngine::getParty(){
    return party;
}

PokemonAttack& GameEngine::getAttack(){
    return attack;
}