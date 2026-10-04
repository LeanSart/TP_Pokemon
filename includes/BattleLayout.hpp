#pragma once
#include <SFML/Graphics.hpp>

/*
Disposition commune aux ecrans de combat (BattleState et WildEncounterState).
Les coordonnees sont calees sur l'image data/BGbattle.png, qui contient
deja deux plateformes : une en haut a droite pour l'adversaire, une en bas a gauche
pour notre pokemon. Le bas de l'ecran (herbe unie) accueille le texte et les boutons.
*/
namespace BattleLayout {
    // Point ou les pokemons posent leurs pattes (milieu de chaque plateforme du decor).
    inline const sf::Vector2f OpponentFeet(720.f, 346.f);
    inline const sf::Vector2f PlayerFeet(143.f, 470.f);

    // Taille maximale (en pixels) de la partie visible des sprites.
    constexpr float OpponentSpriteSize = 180.f;   // plus loin : un peu plus petit
    constexpr float PlayerSpriteSize   = 230.f;   // au premier plan

    // Cartouches nom + PV.
    inline const sf::Vector2f OpponentInfoPos(30.f, 84.f);
    inline const sf::Vector2f PlayerInfoPos(640.f, 452.f);

    // Bas de l'ecran : zone de texte a gauche, colonne de boutons a droite.
    constexpr float BottomTop    = 552.f;
    constexpr float ButtonWidth  = 354.f;
    constexpr float ButtonHeight = 44.f;
    constexpr float ButtonGap    = 8.f;
    inline const sf::Vector2f ButtonSize(ButtonWidth, ButtonHeight);

    // Position du bouton numero index de la colonne (0 = en haut). Un meme bouton garde
    // ainsi la meme place d'une phase a l'autre du combat.
    inline sf::Vector2f buttonSlot(int index) {
        return {640.f, BottomTop + static_cast<float>(index) * (ButtonHeight + ButtonGap)};
    }

    inline const sf::Vector2f LogPanelPos(30.f, BottomTop);
    inline const sf::Vector2f LogPanelSize(590.f, 200.f);
    inline const sf::Vector2f LogTextPos(54.f, BottomTop + 20.f);
    constexpr float LogTextWidth = 542.f;
}
