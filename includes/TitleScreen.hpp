#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "AbstractState.hpp"
#include "Exploration.hpp"
#include "Pokemon.hpp"
#include "Pokedex.hpp"

class TitleScreen : public AbstractState{
    private : 
        Pokemon Starter1 = Pokedex::getPokedex().GetPokemon("Bulbasaur");
        Pokemon Starter2 = Pokedex::getPokedex().GetPokemon("Charmander");
        Pokemon Starter3 = Pokedex::getPokedex().GetPokemon("Squirtle");
    public :
        void run(GameEngine& engine) override;
};