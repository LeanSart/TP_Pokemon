# Review de Code
Auteur : Lucas Raveloarinoro
Date : 17/09/26


## Général

- L'organisation des fichiers du projet est à améliorer, avec les fichiers sources dans un dossier `src`, les fichiers header dans un dossier `inc` et les fichiers d'executables dans un dossier `exe`.
- Les fichiers et dossiers de build (`build` par exemple, ici il n'y en a pas), dossiers internes propres à l'ide que tu utilises (`.vscode` ou `.idea` par exemple) ne sont pas à push dans le projet sur GitHub, et sont à mettre dans le fichier `.gitignore`.
- Le fichier `CMake.txt` est à renommer `CMakeLists.txt`, sinon le compilateur ne le reconnaît pas directement.
- Le code en lui-même ne compile pas pour l'instant, il y a l'air d'avoir une erreur concernant g++..
- Le code dans chaque fichier est de longueur convenable. Le projet n'étant pas encore avancée, il n'y a pas encore de commentaires nécessaires, mais c'est à ne pas oublier au fil du projet, le mieux avec des commentaires directement sous la signature de la méthode.
- Dans le `README.md`, il faudra donner les commandes à donner pour build et exécuter le projet, le mieux serait de faire attention à donner les commandes pour chaque OS qui pourrait être utilisé pour build le projet (Win, Mac, Linux). A terme, il faudra aussi qu'il possède un diagramme de classe.
- Je ne suis pas sûr pour l'utilisation de SFML, je ne sais pas s'il faut le mettre entièrement dans le projet.

## Code 

### main.cpp

Rien à dire, le code est propre avec un fichier à part entière.

### Pokemon.cpp / Pokemon.hpp

Dans la méthode de destructeur, il y a deux actions différentes pour une méthode, c'est préférable de séparer les actions pures (changement de valeur de variables) et les affichage de debug (les `std::cout`).

### SetOfPokemon.cpp / SetOfPokemon.hpp

Les méthodes sont bien implémentées, avec des sorties pour tous les cas possible, tu pourrais aussi utiliser `<stdexept>` pour exploiter et contrôler les erreurs qui peuvent arriver si le comportement n'est pas celui attendu.

### Pokedex.cpp / Pokedex.hpp (bon il est pas là)

Les déclarations de classe, même les classes héritées, doivent être faites dans un fichier header `Pokedex.hpp`.

## Proposition de méthode

Une nouvelle méthode possible serait de sélectionner par exemple un pokemon de départ en commençant la partie, avec un state de starter juste pour le premier pokemon.