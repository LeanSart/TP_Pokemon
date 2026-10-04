#include "PokemonParty.hpp"
#include <stdexcept>

void PokemonParty::addPokemon(std::shared_ptr<Pokemon> pokemon){
    PokeSet.push_back(pokemon);
}

Pokemon PokemonParty::GetPokemon(int indice){
    return Pokemon(*PokeSet.at(indice));
}

Pokemon PokemonParty::GetPokemon(const string& name){
    for (const auto& p : PokeSet) {
        if (p->GetName() == name) {
            return Pokemon(*p);
        }
    }
    throw std::invalid_argument("Pokemon introuvable");
}