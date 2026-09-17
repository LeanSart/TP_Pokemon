#include "Pokemon.hpp"
#include <iostream>

int main() {
    Pokemon Charmander(4, "Charmander", 1, 39, 39, 52, 43);
    // Pokemon Charmanderbis(Charmander);
    // Charmander.DisplayInfo();
    // Charmanderbis.DisplayInfo();
    Pokemon Squirtle(8, "Squirtle", 1, 44, 44, 48, 65);
    Squirtle.isattacking(Charmander);
    Squirtle.isattacking(Charmander);
    Squirtle.isattacking(Charmander);
    Squirtle.isattacking(Charmander);
    Squirtle.isattacking(Charmander);
    std::cout << Charmander.GetName() << " has " << Charmander.GetHitPoint() << " HP left" << std::endl;
    Squirtle.isattacking(Charmander);
    Squirtle.isattacking(Charmander);
    Squirtle.isattacking(Charmander);
    std::cout << Charmander.GetName() << " has " << Charmander.GetHitPoint() << " HP left" << std::endl;
    Squirtle.DisplayInfo();
    return 0;
}
