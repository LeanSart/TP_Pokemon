#pragma once
#include <SFML/Graphics.hpp>

/*
Image d'un pokemon affichee. Charge data/pokemon/<id>.png,
*/
class PokemonSprite {
    private:
        static constexpr float MaxScale = 3.5f;

        sf::Texture texture;
        sf::Sprite sprite;
        bool visible = false;

    public:
        PokemonSprite() = default;
        // Le sprite pointe vers la texture de l'objet : on interdit la copie.
        PokemonSprite(const PokemonSprite&) = delete;
        PokemonSprite& operator=(const PokemonSprite&) = delete;

        // feetPosition : point du sol sous le pokemon (milieu des pattes).
        // maxSize      : taille maximale a l'ecran (en pixels) de la partie visible.
        // mirrored     : retourne l'image horizontalement (pokemon qui regarde vers la droite).
        // Renvoie false (et n'affiche rien) si l'image est introuvable.
        bool load(int id, sf::Vector2f feetPosition, float maxSize, bool mirrored = false);

        void draw(sf::RenderWindow& window) const;
};
