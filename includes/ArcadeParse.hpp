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

/**
 * It defines the pattern of the game libraries.
 */
#define GRAPHIC_LIB_PATTERN R"(lib\/arcade_(ndk\+\+|aalib|ncurses|sdl2|libcaca|allegro5|xlib|gtk\+|sfml|irrlicht|opengl|vulkan|qt5)\.so$)"
/**
 * A macro that defines the pattern of the game libraries.
 */
#define GAME_LIB_PATTERN R"(lib\/arcade_(nibbler|pacman|qix|centiped|solarfox)\.so$)"

namespace Arcade
{
    typedef std::string Game;
    typedef std::string Graphic;

    class ArcadeParse {
    public:
        /**
         * The constructor of the ArcadeParse class. It takes the number of arguments and the arguments given by the user.
         */
        ArcadeParse(int NbArguments, char **Arguments);

        /**
         * The destructor for the ArcadeParse class
         */
        ~ArcadeParse() = default;

        /**
         * Getting the libraries from the command line.
         */
        void GetLibraries();

        /**
         * It checks if the libraries are valid.
         */
        void CheckLibraries();

        /**
         * A static function that checks if the arguments given are valid.
         */
        static void CheckArgument(int NbArguments, char **Arguments);

    protected:
        int CurrentGame;
        int CurrentGraphic;
        std::vector<Game> Games;
        std::vector<Graphic> Graphics;
    };
}