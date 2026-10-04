# TP Pokémon
Bienvenue dans le dépôt du projet **TP Pokémon**. Ce projet a été réalisé dans le cadre de nos travaux pratiques de C++ et implémente une simulation orientée objet avec des mécaniques de jeu Pokémon.

---

## 📁 Structuration du répertoire

Le projet respecte une architecture standard pour séparer le code source, les en-têtes et les fichiers de compilation :

```text
TP_Pokemon/
├── Makefile      # Script de compilation
├── README.md           # Documentation du projet
├── include/            # Fichiers d'en-tête (.h / .hpp)
│   ├── Pokemon.hpp
│   └── ...
├── src/                # Fichiers sources (.cpp)
│   ├── main.cpp
│   ├── Pokemon.cpp
│   └── ...
├── data/                # Images, Listes des pokémons et police d'écriture utilisé dans le projet
│   ├── main.cpp
│   ├── Pokemon.cpp
│   └── ...
└── bin/              # Répertoire généré pour la compilation
```

Pour compiler et exécuter le code, lancez les commandes suivantes depuis la racine du projet :
 - make clean
 - make
 - bin/main.exe

Diagramme de classe : 
[![Architecture diagram](https://gitdiagram.com/diagram-badge.svg)](https://gitdiagram.com/leansart/tp_pokemon?utm_source=readme&utm_medium=badge)

Contraintes techniques : 
 - Polymorphisme : AbstractState.hpp --> Utilisation de différents états pour se "déplacer" dans les différentes pages du jeu
 - Smart Pointer : Utilisation pour les appels aux Pokemons 
 - Lambda Expression : Retirer un pokemon de la liste PokemonAttack dans la méthode removePokemmon --> PokemonAttack.cpp
 - Itérateur dans les boucles for : Méthode GetPokemon --> PokemonParty.hpp
 - Vecteur : PokeSet -> PokemonVector.hpp
 - Type auto : Méthode GetPokemon --> PokemonAttack.hpp
 - Traitement d'exception : Vérification que l'initialisation du jeu s'est faite correctement dans la méthode run --> GameEngine.cpp
 - Design pattern STATE : AbstractState.hpp --> Utilisation de différents états pour se "déplacer" dans les différentes pages du jeu
 - Design pattern SINGLETON : Utilisation dans Pokedex.hpp --> Rend le Pokedex unique
