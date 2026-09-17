#include <string>
#include <vector>
#include <iostream>
#include "Pokemon.hpp"

using std::string;

class SetOfPokemon {
    public :
        std::vector<Pokemon> PokeSet;
        virtual Pokemon GetPokemon(std::vector<Pokemon> PokeSet, int indice);
        virtual Pokemon GetPokemon(std::vector<Pokemon> PokeSet, const string& Name);
        virtual void Display();      
};