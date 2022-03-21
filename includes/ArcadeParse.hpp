/*
** EPITECH PROJECT, 2022
** ArcadeParse
** File description:
** Done
*/

#pragma once

#include <string>
#include <vector>
#include <regex>
#include <filesystem>

#define GRAPHIC_LIB_PATTERN R"(lib\/arcade_(ndk\+\+|aalib|ncurses|sdl2|libcaca|allegro5|xlib|gtk\+|sfml|irrlicht|opengl|vulkan|qt5)\.so$)"
#define GAME_LIB_PATTERN R"(lib\/arcade_(nibbler|pacman|qix|centiped|solarfox)\.so$)"

namespace Arcade
{
    typedef std::string Game;
    typedef std::string Graphic;

    class ArcadeParse {
    public:
        ArcadeParse(int NbArguments, char **Arguments);
        ~ArcadeParse() = default;
        void GetLibraries();
        void CheckLibraries();
        static void CheckArgument(int NbArguments, char **Arguments);

    protected:
        int CurrentGame;
        int CurrentGraphic;
        std::vector<Game> Games;
        std::vector<Graphic> Graphics;
    };
}