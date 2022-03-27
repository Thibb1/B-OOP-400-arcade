/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** TODO
*/

#pragma once

#include <string>
#include <thread>
#include <fstream>

#include "ArcadeParse.hpp"
#include "Library.hpp"
#include "Display.hpp"
#include "Game.hpp"

namespace Arcade
{
    typedef std::string Player;

    class ArcadeBorne : public ArcadeParse {
    public:
        ArcadeBorne(int NbArguments, char **Arguments);
        ~ArcadeBorne() = default;
        void DisplayLibs();
        void GetPlayerName();
        void LoadGraphicLib();
        void LoadGameLib();
        static int Modulo(int, int);
    private:
        Player player;
        Library libraries;
        bool InMenu;

        void SaveScore();
    };
}