#include <string>
#include <iostream>

using std::string;

class Pokemon {
private:
    int id = 0;
    string name = "Unnamed";
    int evolution = 0;
    double hitPointMax = 0;
    double hitPoint = 0;
    double attack = 0;
    double defense = 0;
public:
    Pokemon() = delete;
    Pokemon(int id, const string& name, int evolution, double hitPointMax, double hitPoint, double attack, double defense);
    Pokemon(const Pokemon& anotherPokemon);
    ~Pokemon();
    void DisplayInfo() const;
    int GetID();
    string GetName();
    int GetEvolution();
    double GetHitPointMax();
    double GetHitPoint();
    void SetHitPoint(double NewhitPoint);
    double GetAttack();
    double GetDefense();
    void isattacking(Pokemon& Defender) const;
    int Getnumber_of_pokemon();
};
