#include "AbstractState.hpp"

int AbstractState::choice(int min, int max){
    int choice;
    while (true){
        if (std::cin >> choice) {
            if (choice >= min && choice <= max) {
                return choice;
            } else {
                std::cout << "Erreur : la valeur doit être comprise entre " << min << " et " << max << ".\n";
            }
        } else {
            std::cout << "Erreur : saisie invalide. Veuillez entrer un nombre.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}