#include <random>
#include "Exploration.hpp"
#include "GameEngine.hpp"
#include "BattleState.hpp"
#include "WildEncounterState.hpp"
#include "PokemonPartyViewver.hpp"
#include "PokemonAttackViewver.hpp"

void Exploration::run(GameEngine& engine){
    std::cout << "\nQue voulez-vous faire ?" << std::endl;
    std::cout << "1. Continuer a marcher" << std::endl;
    std::cout << "2. Voir l'ensemble de mes pokemons" << std::endl;
    std::cout << "3. Voir mon equipe" << std::endl;
    std::cout << "4. Quitter le jeu" << std::endl;

    int playerchoice = choice(1, 4);
    if (playerchoice == 1){
        int randint = engine.random();
        if (randint <= 25){
            engine.changeState(std::make_unique<WildEncounterState>()); //Meet a new pokemon
        }
        if (25 < randint <= 75){
            engine.changeState(std::make_unique<BattleState>()); //Meet an opponant
        }
        else {
            std::cout << "Il n'y a pas grand chose par ici..." << std::endl;
        }
    }
    if (playerchoice == 2){
        engine.changeState(std::make_unique<PokemonPartyViewver>());
    }
    if (playerchoice == 3){
        engine.changeState(std::make_unique<PokemonAttackViewver>());
    }
    if (playerchoice == 4){
        std::cout << "Fin de la partie initiee par le joueur !" << std::endl;
        engine.quit();
    }
}