#include "Exploration.hpp"
#include "GameEngine.hpp"

void Exploration::run(GameEngine& engine){
    std::cout << "\nQue voulez-vous faire ?" << std::endl;
    std::cout << "1. ..." << std::endl;
    std::cout << "2. ..." << std::endl;
    std::cout << "3. ..." << std::endl;
    std::cout << "4. Quitter le jeu" << std::endl;

    int playerchoice = choice(1, 4);
    if (playerchoice == 1){

    }
    if (playerchoice == 2){
        
    }
    if (playerchoice == 3){
        
    }
    if (playerchoice == 4){
        std::cout << "Fin de la partie initiee par le joueur !" << std::endl;
        engine.quit();
    }
}