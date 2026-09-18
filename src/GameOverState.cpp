#include "GameOverState.hpp"
#include <string>
#include "GameEngine.hpp"

void GameOverState::run(GameEngine& engine){
    std::cout << "================================" << std::endl;
    std::cout << "        G A M E   O V E R       " << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Appuyez sur <ENTREE> pour sortir du jeu..." << std::endl;

    std::string dummy;
    std::getline(std::cin, dummy);

    engine.quit();
}