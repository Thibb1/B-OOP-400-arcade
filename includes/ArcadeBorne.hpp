/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** TODO
*/

#pragma once

#include <string>
#include <thread>

#include "ArcadeParse.hpp"
#include "Library.hpp"
#include "Display.hpp"
#include "Game.hpp"

namespace Arcade
{
    typedef std::string Player;
    typedef Library<IGame> LibraryGame;
    typedef Library<IDisplay> LibraryDisplay;

    class ArcadeBorne : public ArcadeParse {
    public:
        ArcadeBorne(int NbArguments, char **Arguments);
        ~ArcadeBorne() = default;
        void DisplayLibs();
        void GetPlayerName();
        void LoadGraphicLib();
        void LoadGameLib();
    private:
        Player player;
        Library<IGame> game;
        Library<IDisplay> display;
    };
}