#pragma once
#include "PokemonVector.hpp"

/*
Classe PokemonParty héritée de PokemonVector : 
Liste de l'ensemble des pokemon possédé par le joueur. Il ne peut pas en avoir plus que le pokedex
*/
class PokemonParty : public PokemonVector {
    public :
        void addPokemon(const Pokemon& pokemon);
        Pokemon GetPokemon(int indice) override;
        Pokemon GetPokemon(const string& name) override;
};