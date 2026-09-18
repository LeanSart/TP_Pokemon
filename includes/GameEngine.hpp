#pragma once
#include <random>
#include <memory>
#include "AbstractState.hpp"
#include "PokemonParty.hpp"
#include "PokemonAttack.hpp"

/* 
Classe moteur du jeu : Permet de connaitre l'etat actuel et implémente la fonctionnalité d'aléatoire
*/
class GameEngine{
private:
    std::unique_ptr<AbstractState> currentState;
    PokemonParty party;
    PokemonAttack attack;
    bool running = true;
    std::mt19937 randomgenerator;

public :
    void run();
    void changeState(std::unique_ptr<AbstractState> newState);
    void quit();
    int random();
    PokemonParty& getParty();
    PokemonAttack& getAttack();
};