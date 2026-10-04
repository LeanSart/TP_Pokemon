#pragma once
#include "PokemonVector.hpp"
#include <algorithm>

/*
Classe PokemonAttack héritée de PokemonVector : 
Liste de l'ensemble des pokemon utilisable lors d'un combat. Il y en a un maximum de 6. 
*/

class PokemonAttack : public PokemonVector {
    public :
    void addPokemon(std::shared_ptr<Pokemon> pokemon);
    void removePokemon(std::shared_ptr<Pokemon> pokemon);
    Pokemon GetPokemon(int indice) override;
    Pokemon GetPokemon(const string& Name) override;
};