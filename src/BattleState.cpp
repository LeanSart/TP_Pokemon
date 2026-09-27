#include <random>
#include "BattleState.hpp"
#include "GameEngine.hpp"
#include "Pokedex.hpp"

void BattleState::run(GameEngine &engine){
    std::shared_ptr<Pokemon> WildPokemon = std::make_shared<Pokemon>(Pokedex::getPokedex().GetPokemon(int(engine.random())));
    std::cout << "Vous rencontrez Red avec " << WildPokemon->GetName() << " (HP : " << WildPokemon->GetHitPoint() << " ATK : " << WildPokemon->GetAttack() << " DEF : " << WildPokemon->GetDefense() << ")" << std::endl;
    std::cout << "1. Attaquer" << std::endl;
    std::cout << "2. Quitter le jeu" << std::endl;

    int playerchoice = choice(1, 2);
    if (playerchoice == 1){
        bool battle_active = true;
        std::shared_ptr<Pokemon> fighter = nullptr;
        for(auto& p : engine.getAttack()){
            if (p->GetHitPoint() > 0) {
                fighter = p;
                break;
            }
        }
        if (fighter == nullptr) {
            std::cout << "Vous n'avez plus de Pokemon en etat de se battre !" << std::endl;
            engine.changeState(std::make_unique<GameOverState>());
        }

        while (battle_active && WildPokemon->GetHitPoint() != 0){
            int randint_attack = engine.random();
            if (randint_attack <= 15){
                std::cout << WildPokemon->GetName() << " a feinte l'attaque..." << std::endl;
            }
            else {
                fighter->isattacking(*WildPokemon);
            }
            int randint_defense = engine.random();
            if (randint_defense <= 15){
                std::cout << fighter->GetName() << " a feinte l'attaque..." << std::endl;
            }
            else {
                WildPokemon->isattacking(*fighter);
            }
            if (fighter->GetHitPoint() <= 0){
                std::cout << fighter->GetName() << " a ete vaincu..." << std::endl;
                std::shared_ptr<Pokemon> next_fighter = nullptr;
                for(auto& p : engine.getAttack()){
                    if (p->GetHitPoint() > 0) {
                        next_fighter = p;
                        break;
                    }
                }
                if (next_fighter == nullptr) {
                    std::cout << "Tous vos Pokemon sont hors combat. Vous n'avez plus la force de continuer..." << std::endl;
                    engine.changeState(std::make_unique<GameOverState>());
                    battle_active = false;
                }
                else {
                    std::cout << "1. Continuer le combat avec " << next_fighter->GetName() << std::endl;
                    std::cout << "2. Prendre la fuite" << std::endl;
                    int choice;
                    std::cin >> choice;
                    if (choice == 1) {
                        fighter = next_fighter;
                        std::cout << "En avant, " << fighter->GetName() << " !" << std::endl;
                    } 
                    else {
                        std::cout << "Vous prenez la fuite..." << std::endl;
                        engine.changeState(std::make_unique<Exploration>());
                        battle_active = false;
                    }
                }
            }
        }
        if (WildPokemon->GetHitPoint() <= 0){
            std::cout << WildPokemon->GetName() << " a ete vaincu !" << std::endl;
            engine.changeState(std::make_unique<Exploration>()); 
        }
    }
    if (playerchoice == 2){
        std::cout << "Fin de la partie initiee par le joueur !" << std::endl;
        engine.quit();
    }
}