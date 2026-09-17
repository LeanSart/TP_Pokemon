#include "Pokemon.hpp"
#include <iostream>

static int number_of_pokemon = 0;

Pokemon::Pokemon(int id, const string& name, int evolution, double hitPointMax, double hitPoint, double attack, double defense)
    : id(id), name(name), evolution(evolution), hitPointMax(hitPointMax), hitPoint(hitPointMax), attack(attack), defense(defense) {number_of_pokemon++;}

Pokemon::Pokemon(const Pokemon& anotherPokemon)
    : id(anotherPokemon.id), name(anotherPokemon.name), evolution(anotherPokemon.evolution), hitPointMax(anotherPokemon.hitPointMax), hitPoint(anotherPokemon.hitPoint), attack(anotherPokemon.attack), defense(anotherPokemon.defense) {number_of_pokemon++;}

Pokemon::~Pokemon() {
    number_of_pokemon--;
    std::cout << "Destroyed" << std::endl;
}
int Pokemon::Getnumber_of_pokemon(){
    return number_of_pokemon;
}
int Pokemon::GetID(){
    return id;
}

string Pokemon::GetName(){
    return name;
}

int Pokemon::GetEvolution(){
    return evolution;
}

double Pokemon::GetHitPointMax(){
    return hitPointMax;
}

double Pokemon::GetHitPoint(){
    return hitPoint;
}
void Pokemon::SetHitPoint(double NewhitPoint){
    hitPoint = NewhitPoint;
}

double Pokemon::GetAttack(){
    return attack;
}

double Pokemon::GetDefense(){
    return defense;
}


void Pokemon::isattacking(Pokemon& Defender) const{
    double diffLife = this->attack - Defender.GetDefense();
    double HPdef = Defender.GetHitPoint();
    if (diffLife > 0) {
        if ((HPdef < diffLife) && (HPdef != 0)) {
            Defender.SetHitPoint(0);
            std::cout << Defender.GetName() << " Died..." << std::endl;
        }
        if (HPdef == 0) {
            std::cout << Defender.GetName() << " Died..." << std::endl;
        }
        if ((HPdef >= diffLife) && (HPdef != 0)){
            Defender.SetHitPoint(HPdef - diffLife);
        }
    }
    else {
        std::cout << "The attack of "<< this->name << " has been unsuccessful" << std::endl;
    }
}
void Pokemon::DisplayInfo() const {
    std::cout << "ID :" << id << std::endl;
    std::cout << "Name :" << name << std::endl;
    std::cout << "Evolution :" << evolution << std::endl;
    std::cout << "HitpointMax :" << hitPointMax << std::endl;
    std::cout << "Hitpoint :" << hitPoint << std::endl;
    std::cout << "Attack :" << attack << std::endl;
    std::cout << "Defense :" << defense << std::endl;
}