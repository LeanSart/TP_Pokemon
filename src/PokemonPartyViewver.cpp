#include "PokemonPartyViewver.hpp"
#include "GameEngine.hpp"

void PokemonPartyViewver::run(GameEngine& engine){
    std::cout << "Votre Pokedex : " << std::endl;
    for (auto& p : engine.getParty()){
        std::cout << " - " << p->GetName() << " ( " << p->GetHitPoint() << " HP )"<< std::endl;
    }

    engine.changeState(std::make_unique<Exploration>());
};