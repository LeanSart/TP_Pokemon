#pragma once
#include <SFML/Graphics.hpp>

/*
Constantes visuelles partagees par tous les ecrans du jeu : couleurs,
tailles de police, dimensions de la fenetre. Centraliser ces valeurs ici
evite de les dupliquer (et de les desynchroniser) dans chaque etat.
*/
namespace Theme {
    constexpr unsigned int WindowWidth  = 1024;
    constexpr unsigned int WindowHeight = 768;

    inline const sf::Color Background    (24, 28, 44);
    inline const sf::Color Panel         (36, 42, 66);
    inline const sf::Color PanelLight    (48, 56, 86);
    inline const sf::Color PanelOverlay  (24, 28, 44, 215);   // panneau semi-transparent pose sur un decor
    inline const sf::Color ButtonNormal  (58, 68, 102);
    inline const sf::Color ButtonHover   (86, 100, 148);
    inline const sf::Color ButtonSelected(226, 160, 60);
    inline const sf::Color TextPrimary   (240, 240, 245);
    inline const sf::Color TextSecondary (170, 176, 200);
    inline const sf::Color Accent        (226, 160, 60);
    inline const sf::Color HPGreen       (94, 186, 105);
    inline const sf::Color HPYellow      (230, 196, 70);
    inline const sf::Color HPRed         (206, 70, 70);

    constexpr unsigned int TitleSize      = 30;
    constexpr unsigned int SubtitleSize   = 18;
    constexpr unsigned int TextSize       = 16;
    constexpr unsigned int ButtonTextSize = 14;
}
