#include "Pokemon.hpp"
#include <iostream>

Pokemon::Pokemon(int id, const string& name, int generation, double hitPointMax, double hitPoint, double attack, double defense)
    : id(id), name(name), generation(generation), hitPointMax(hitPointMax), hitPoint(hitPoint), attack(attack), defense(defense) {}

Pokemon::Pokemon(const Pokemon& anotherPokemon)
    : id(anotherPokemon.id), name(anotherPokemon.name), generation(anotherPokemon.generation), hitPointMax(anotherPokemon.hitPointMax), hitPoint(anotherPokemon.hitPoint), attack(anotherPokemon.attack), defense(anotherPokemon.defense) {}

Pokemon::~Pokemon() {}

int Pokemon::GetID(){
    return id;
}

string Pokemon::GetName() const{
    return name;
}

int Pokemon::GetGeneration(){
    return generation;
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
    double damage = this->attack - Defender.GetDefense();
    if (damage <= 0) {
        damage = 1;
    }
    double HPdef = Defender.GetHitPoint();
    if (HPdef <= damage) {
        Defender.SetHitPoint(0);
    } 
    else {
        Defender.SetHitPoint(HPdef - damage);
    }
}
void Pokemon::DisplayInfo() const {
    std::cout << "ID :" << id << std::endl;
    std::cout << "Name :" << name << std::endl;
    std::cout << "Generation :" << generation << std::endl;
    std::cout << "HitpointMax :" << hitPointMax << std::endl;
    std::cout << "Hitpoint :" << hitPoint << std::endl;
    std::cout << "Attack :" << attack << std::endl;
    std::cout << "Defense :" << defense << std::endl;
}