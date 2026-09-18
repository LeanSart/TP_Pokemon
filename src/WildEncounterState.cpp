#include "WildEncounterState.hpp"
#include "GameEngine.hpp"
#include "Pokemon.hpp"
#include "Pokedex.hpp"

void WildEncounterState::run(GameEngine& engine){
    Pokemon fighter;
    Pokemon WildPokemon = Pokedex::getPokedex().GetPokemon(int(engine.random())); 
    std::cout << "Vous rencontrez " << WildPokemon.GetName() << std::endl;
    std::cout << "1. Attaquer" << std::endl;
    std::cout << "2. Fuir" << std::endl;
    std::cout << "3. Utiliser une Pokeball" << std::endl;
    std::cout << "4. Quitter le jeu" << std::endl;

    int playerchoice = choice(1, 4);
    if (playerchoice == 1){
        int randint = engine.random();
        if (randint <= 5){
            std::cout << "L'attaque a echoue..." << std::endl;
        }
        else {
            PokemonAttack &ListPokemonAttack = engine.getAttack();
            for(Pokemon p : ListPokemonAttack){
                if (p.GetHitPoint() != 0) {
                    fighter = p;
                    break;
                }
            }
            while (fighter.GetHitPoint() != 0 && WildPokemon.GetHitPoint() != 0){
                int randint_attack = engine.random();
                if (randint_attack <= 15){
                std::cout << WildPokemon.GetName() << "a feinte l'attaque..." << std::endl;
                }
                else {
                    fighter.isattacking(WildPokemon);
                }
                int randint_defense = engine.random();
                if (randint_defense <= 15){
                std::cout << fighter.GetName() << "a feinte l'attaque..." << std::endl;
                }
                else {
                    WildPokemon.isattacking(fighter);
                }
            }
            if (fighter.GetHitPoint() == 0){
                std::cout << fighter.GetName() << "a ete vaincu..." << std::endl;
                engine.changeState(std::make_unique<GameOverState>());
            }
            else if (WildPokemon.GetHitPoint() == 0){
                std::cout << WildPokemon.GetName() << "a ete vaincu..." << std::endl;
                engine.changeState(std::make_unique<Exploration>()); 
            }
        }
    }
    if (playerchoice == 2){
        std::cout << "Vous prenez la fuite..." << std::endl;
        engine.changeState(std::make_unique<Exploration>());
    }
    if (playerchoice == 3){
        int randint = engine.random();
        if (randint <= 75){
            std::cout << WildPokemon.GetName() << "a ete capture..." << std::endl;
            engine.getParty().addPokemon(WildPokemon);
            engine.changeState(std::make_unique<Exploration>());
        }
        else {
            std::cout << WildPokemon.GetName() << "s'est echappe..." << std::endl;
            engine.changeState(std::make_unique<Exploration>());
        }
    }
    if (playerchoice == 4){
        std::cout << "Fin de la partie initiee par le joueur !" << std::endl;
        engine.quit();
    }
};