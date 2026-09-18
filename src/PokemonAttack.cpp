#include "PokemonAttack.hpp"

void PokemonAttack::addPokemon(const Pokemon& pokemon){
    PokeSet.push_back(std::make_shared<Pokemon>(pokemon));
}

void PokemonAttack::removePokemon(const Pokemon& pokemon){
    PokeSet.pop_back(std::make_shared<Pokemon>(pokemon));
}

Pokemon PokemonAttack::GetPokemon(int indice){
    return Pokemon(*PokeSet.at(indice));
}

Pokemon PokemonAttack::GetPokemon(const string& name){
    for (const auto& p : PokeSet) {
        if (p->GetName() == name) {
            return Pokemon(*p);
        }
    }
    return Pokemon(0, "Unnamed", 0, 0, 0, 0, 0);
}