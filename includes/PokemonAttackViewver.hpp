#pragma once
#include "AbstractState.hpp"
#include "GameEngine.hpp"

/*
Etat de visualisation et de modification de son équipe pour combattre
*/
class PokemonAttackViewver : AbstractState {
    public :
        void PokemonAttackViewver::run(GameEngine &engine) override;
};