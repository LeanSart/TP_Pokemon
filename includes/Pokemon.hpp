#pragma once
#include <string>
#include <iostream>

using std::string;
/*
Class Pokemon : création de l'objet Pokemon avec un id, un nom, sa génération, ses HPmax, ses HP, son attaque et sa défence
Tous les attributs ont leur getter, ses HP ont un setter pour permettre de faire évoluer les PV du pokemon.
Il existe aussi une méthode pour attaquer un autre Pokémon. 
*/
class Pokemon {
private:
    int id = 0;
    string name = "Unnamed";
    int generation = 0;
    double hitPointMax = 0;
    double hitPoint = 0;
    double attack = 0;
    double defense = 0;
public:
    ~Pokemon();
    Pokemon() = delete;
    Pokemon(int id, const string& name, int generation, double hitPointMax, double hitPoint, double attack, double defense);
    Pokemon(const Pokemon& anotherPokemon);
    void DisplayInfo() const;
    int GetID();
    string GetName() const;
    int GetGeneration();
    double GetHitPointMax();
    double GetHitPoint();
    void SetHitPoint(double NewhitPoint);
    double GetAttack();
    double GetDefense();
    void isattacking(Pokemon& Defender) const;
};
