
#include "SetOfPokemon.hpp"
#include <iostream>

Pokemon SetOfPokemon::GetPokemon(std::vector<Pokemon> PokeSet, int indice){
    return PokeSet.at(indice);
}

Pokemon SetOfPokemon::GetPokemon(std::vector<Pokemon> PokeSet, const string& Name){
    for (Pokemon p : PokeSet) {
        if (p.GetName() == Name) {
            return p;
        }
    }
    return Pokemon(0, "Unnamed", 0 ,0 ,0 ,0 ,0);
}

void SetOfPokemon::Display() {
    for (Pokemon p : PokeSet) {
        std::cout << p.GetName() << std::endl;
    }
}






/* #include "Pokedex.hpp"
#include "Pokemon.hpp"
#include <iostream>

Pokedex::Pokedex(string fileName):SetOfPokemon() {

    std::cout << "*** Constructeur du Pokedex ***" << std::endl;

    std::ifstream file(fileName);
    if(!file.is_open()){
        std::cerr<<"File "<<fileName<<" not found "<<std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
    //    std::cout << line << std::endl;
        std::stringstream inputstringstream(line);
        std::string cell;
        std::vector<std::string> lineData;

        while(std::getline(inputstringstream,cell,',')){
            lineData.push_back(cell);
        }
        int id = std::stoi(lineData.at(0));
        double attackValue = std::stod(lineData.at(6));
        double hitPoint = std::stod(lineData.at(5));
        double defenseValue = std::stod(lineData.at(7));
        int generation = std::stoi(lineData.at(11));

        arrayOfPokemon.push_back(new Pokemon(lineData.at(1),id,hitPoint,attackValue,
                                             defenseValue,generation));
    }
}
*/


