#include "SetOfPokemon.hpp"

class Pokedex : public SetOfPokemon {
    private:
        Pokedex() {
            // Crée le pokedex avec tous les pokemons possible, la liste est contenue dans un csv sur moodle et fonction lireCSV dans le diapo cours
        };
    public:
        static Pokedex getPokedex() {
            static Pokedex Pokedex;
            return Pokedex;
        };
        
        Pokemon GetPokemon(const string& Name) {
            SetOfPokemon::GetPokemon(Pokedex, Name);
        }
};