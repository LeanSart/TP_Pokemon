#pragma once
#include "PokemonVector.hpp"

/*
Classe Pokedex héritée de PokemonVector : 
Utilise le fichier pokedex.csv pour recupérer tous les pokemon du jeu. le constructeur de pokedex est un singleton pour n'avoir qu'un pokedex dans le jeu. 
On pourra par la suite uniquement dupliquer un pokemon du pokedex sans possibilité de créer un pokemon. 
*/
class Pokedex : public PokemonVector {
    private:
        Pokedex() {
            SetPokedex("data/pokedex.csv");
        };
    public:
        Pokedex(const Pokedex&) = delete;
        Pokedex& operator=(const Pokedex&) = delete;
        static Pokedex& getPokedex(){
            static Pokedex instance;
            return instance;
        };
        Pokemon GetPokemon(int indice) override;
        Pokemon GetPokemon(const string& name) override;
        void SetPokedex(const std::string& filename);
};
