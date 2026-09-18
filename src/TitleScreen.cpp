#include "GameEngine.hpp"
#include "TitleScreen.hpp"
#include "Pokemon.hpp"
#include "Exploration.hpp"

void TitleScreen::run(GameEngine& engine){
    std::cout << "=======================================" << std::endl;
    std::cout << "        POKEMON : EDITION ENSEA        " << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "Appuyez sur <ENTREE> pour demarrer le jeu..." << std::endl;

    std::string dummy;
    std::getline(std::cin, dummy);

    std::cout << "\nBienvenue dans Pokemon !" << std::endl;
    std::cout << "Le Professeur Chen vous attend dans son laboratoire à Cergy." << std::endl;
    std::cout << "Il est temps de choisir votre premier partenaire :\n" << std::endl;
    std::cout << "1. " << Starter1.GetName() << std::endl;
    std::cout << "2. " << Starter2.GetName() << std::endl;
    std::cout << "3. " << Starter3.GetName() << std::endl;
    int starterChoice = choice(1, 3);

    switch (starterChoice) {
        case 1:
            std::cout << "\nFelicitations ! Vous avez choisi " << Starter1.GetName() << " !" << std::endl;
            engine.getParty().addPokemon(Starter1);
            break;
        case 2:
            std::cout << "\nFelicitations ! Vous avez choisi " << Starter2.GetName() << " !" << std::endl;
            engine.getParty().addPokemon(Starter2);
            break;
        case 3:
            std::cout << "\nFelicitations ! Vous avez choisi " << Starter3.GetName() << " !" << std::endl;
            engine.getParty().addPokemon(Starter3);
            break;
    }

    std::cout << "Votre aventure commence maintenant...\n" << std::endl;
    engine.changeState(std::make_unique<Exploration>());
};