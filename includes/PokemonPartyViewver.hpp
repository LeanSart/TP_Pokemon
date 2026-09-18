#pragma once
#include "AbstractState.hpp"
#include "Exploration.hpp"

/*
Etat de visualisation l'ensemble de ses Pokemons
*/

class PokemonPartyViewver : public AbstractState{
    public :
        void run(GameEngine& engine) override;
};