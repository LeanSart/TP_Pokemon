#pragma once
#include "PokemonVector.hpp"

/*
Classe PokemonAttack héritée de PokemonVector : 
Liste de l'ensemble des pokemon utilisable lors d'un combat. Il y en a un maximum de 6. 
*/

class PokemonAttack : public PokemonVector {
    public :
    void addPokemon(const Pokemon& pokemon);
    void removePokemon(const Pokemon& pokemon);
    Pokemon GetPokemon(int indice) override;
    Pokemon GetPokemon(const string& Name) override;
};