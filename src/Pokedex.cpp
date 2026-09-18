#include "Pokedex.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Pokemon Pokedex::GetPokemon(int indice){
    return Pokemon(*PokeSet.at(indice));
}

Pokemon Pokedex::GetPokemon(const string& name) {
    for (const auto& p : PokeSet) {
        if (p->GetName() == name) {
            return Pokemon(*p);
        }
    }
    return Pokemon(0, "Unnamed", 0 ,0 ,0 ,0 ,0);
}

void Pokedex::SetPokedex(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr<<"File "<<filename<<" not found "<<std::endl;
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

        PokeSet.push_back(std::make_shared<Pokemon>(id, lineData.at(1), generation,
                                hitPoint, hitPoint,
                                attackValue, defenseValue));
    };
};



