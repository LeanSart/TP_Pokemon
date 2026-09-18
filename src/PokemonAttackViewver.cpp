#include "PokemonAttackViewver.hpp"

void PokemonAttackViewver::run(GameEngine &engine){
    std::cout << "Votre équipe : " << std::endl;
    for (Pokemon p : GameEngine.getAttack()){
        std::cout << " - " << p.GetName() << " ( " << p.GetHitPoint() << " HP )"<< std::endl;
    }
    std::cout << "\nQue voulez-vous faire ?" << std::endl;
    std::cout << "1. Modifier des Pokemons dans l'equipe" << std::endl;
    std::cout << "2. Retourner explorer" << std::endl;
    int playerchoice = choice(1, 2);
    if (playerchoice == 2){
        engine.changeState(std::make_unique<Exploration>());
    }
    if (playerchoice == 1){
        // TO DO
    }
}