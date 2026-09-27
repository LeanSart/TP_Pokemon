#include "WildEncounterState.hpp"
#include "GameEngine.hpp"
#include "Pokemon.hpp"
#include "Pokedex.hpp"

void WildEncounterState::run(GameEngine& engine){
    bool battle_active = true;
    std::shared_ptr<Pokemon> fighter = nullptr;
    std::shared_ptr<Pokemon> WildPokemon = std::make_shared<Pokemon>(Pokedex::getPokedex().GetPokemon(int(engine.random())));
    std::cout << "Vous rencontrez " << WildPokemon->GetName() << " (HP : " << WildPokemon->GetHitPoint() << " ATK : " << WildPokemon->GetAttack() << " DEF : " << WildPokemon->GetDefense() << ")" << std::endl;
    std::cout << "1. Attaquer" << std::endl;
    std::cout << "2. Fuir" << std::endl;
    std::cout << "3. Utiliser une Pokeball" <<  std::endl;
    std::cout << "4. Quitter le jeu" << std::endl;

    int playerchoice = choice(1, 4);
    if (playerchoice == 1){
        for(auto& p : engine.getAttack()){
            if (p->GetHitPoint() != 0) {
                fighter = p;
                break;
            }
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
            std::cout << WildPokemon->GetName() << " a ete vaincu..." << std::endl;
            engine.changeState(std::make_unique<Exploration>()); 
        }
    }
    if (playerchoice == 2){
        std::cout << "Vous prenez la fuite..." << std::endl;
        engine.changeState(std::make_unique<Exploration>());
    }
    if (playerchoice == 3){
        int randint = engine.random();
        if (randint <= 85){
            std::cout << WildPokemon->GetName() << " a ete capture..." << std::endl;
            engine.getParty().addPokemon(*WildPokemon);
            engine.changeState(std::make_unique<Exploration>());
        }
        else {
            std::cout << WildPokemon->GetName() << " s'est echappe..." << std::endl;
            engine.changeState(std::make_unique<Exploration>());
        }
    }
    if (playerchoice == 4){
        std::cout << "Fin de la partie initiee par le joueur !" << std::endl;
        engine.quit();
    }
};