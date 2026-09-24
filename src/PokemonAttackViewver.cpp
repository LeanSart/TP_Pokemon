#include "PokemonAttackViewver.hpp"
#include "GameEngine.hpp"
#include "Exploration.hpp"

void PokemonAttackViewver::run(GameEngine &engine){
    std::cout << "Votre équipe : " << std::endl;
    if (engine.getAttack().size() == 0) {
        std::cout << " Votre equipe est vide" << std::endl;
    } else {
        for (auto& p : engine.getAttack()) { 
            std::cout << " - " << p->GetName() << " ( " << p->GetHitPoint() << " HP )"<< std::endl;
        }
    }
    std::cout << "\nQue voulez-vous faire ?" << std::endl;
    std::cout << "1. Modifier des Pokemons dans l'equipe" << std::endl;
    std::cout << "2. Retourner explorer" << std::endl;
    int playerchoice = choice(1, 2);
    if (playerchoice == 2){
        engine.changeState(std::make_unique<Exploration>());
    }
    if (playerchoice == 1){
        std::cout << "\n--- Modification de l'equipe ---" << std::endl;
        std::cout << "1. Ajouter un Pokemon a l'equipe d'attaque" << std::endl;
        std::cout << "2. Retirer un Pokemon de l'equipe d'attaque" << std::endl;
        std::cout << "3. Voir l'ensemble de mes pokemons" << std::endl; 
        std::cout << "4. Annuler" << std::endl;
        
        int modifChoice = choice(1, 3);
        std::string pokeName;
        
        if (modifChoice == 1) {
            if (engine.getAttack().size() >= 6) {
                std::cout << "Impossible d'ajouter : votre equipe est deja pleine (6 Pokemons maximum) !" << std::endl;
            } else {
                std::cout << "Entrez le nom du Pokemon a ajouter (depuis votre Party) : ";
                std::cin >> pokeName;
                
                try {
                    Pokemon p = engine.getParty().GetPokemon(pokeName);
                    engine.getAttack().addPokemon(p);
                    std::cout << p.GetName() << " a bien ete ajoute a l'equipe de combat !" << std::endl;
                } catch (...) {
                    std::cout << "Erreur : Pokemon introuvable dans votre collection." << std::endl;
                }
            }
        } 
        else if (modifChoice == 2) {
            if (engine.getAttack().size() == 0) {
                std::cout << "Impossible de retirer un Pokemon : votre equipe est vide !" << std::endl;
            } else { 
                std::cout << "Entrez le nom du Pokemon a retirer de l'equipe : ";
                std::cin >> pokeName;
                
                try {
                    Pokemon p = engine.getAttack().GetPokemon(pokeName);
                    engine.getAttack().removePokemon(p);
                    std::cout << p.GetName() << " a ete retire de l'equipe de combat !" << std::endl;
                } catch (...) {
                    std::cout << "Erreur : Ce Pokemon n'est pas dans votre equipe actuelle." << std::endl;
                }
            }
        } 
        else if (modifChoice == 3 ) {
            for (auto& p : engine.getAttack()) { 
                std::cout << " - " << p->GetName() << " ( " << p->GetHitPoint() << " HP )"<< std::endl;
            }
        }
    }
}