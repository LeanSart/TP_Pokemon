#include <random>
#include "BattleState.hpp"
#include "GameEngine.hpp"
#include "Pokedex.hpp"

void BattleState::run(GameEngine &engine){
    std::cout << "Vous rencontrez Red" << std::endl;
    std::cout << "1. Attaquer" << std::endl;
    std::cout << "2. Quitter le jeu" << std::endl;

    int playerchoice = choice(1, 2);
    if (playerchoice == 1){
        int randint = engine.random();
        if (randint <= 5){
            std::cout << "L'attaque a echoue..." << std::endl;
        }
        else {
            PokemonAttack &ListPokemonAttack = engine.getAttack();
            std::shared_ptr<Pokemon> fighter = nullptr;
            std::shared_ptr<Pokemon> WildPokemon = std::make_shared<Pokemon>(Pokedex::getPokedex().GetPokemon(int(engine.random())));
            for(auto& p : ListPokemonAttack){
                if (p->GetHitPoint() != 0) {
                    fighter = p;
                    break;
                }
            }
            while (fighter->GetHitPoint() != 0 && WildPokemon->GetHitPoint() != 0){
                int randint_attack = engine.random();
                if (randint_attack <= 15){
                std::cout << WildPokemon->GetName() << "a feinte l'attaque..." << std::endl;
                }
                else {
                    fighter->isattacking(*WildPokemon);
                }
                int randint_defense = engine.random();
                if (randint_defense <= 15){
                std::cout << fighter->GetName() << "a feinte l'attaque..." << std::endl;
                }
                else {
                    WildPokemon->isattacking(*fighter);
                }
            }
            if (fighter->GetHitPoint() == 0){
                std::cout << fighter->GetName() << "a ete vaincu..." << std::endl;
                engine.changeState(std::make_unique<GameOverState>());
            }
            else if (WildPokemon->GetHitPoint() == 0){
                std::cout << WildPokemon->GetName() << "a ete vaincu..." << std::endl;
                engine.changeState(std::make_unique<Exploration>()); 
            }
        }
    }
    if (playerchoice == 2){
        std::cout << "Fin de la partie initiee par le joueur !" << std::endl;
        engine.quit();
    }
}