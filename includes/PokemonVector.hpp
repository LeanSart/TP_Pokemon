#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "Pokemon.hpp"

using std::string;

/*
Classe abstraite PokemonVector : Permet de faire des listes de Pokemon --> Pokedex / PokemonParty / PokemonAttack
*/
class PokemonVector {
    protected :
        std::vector<std::shared_ptr<Pokemon>> PokeSet;
    public :
        virtual Pokemon GetPokemon(int indice) = 0;
        virtual Pokemon GetPokemon(const string& Name) = 0;
        virtual ~PokemonVector() = default;
};