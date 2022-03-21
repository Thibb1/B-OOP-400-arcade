/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** TODO
*/

#pragma once

#include <string>

#include "ArcadeParse.hpp"

namespace Arcade
{
    typedef std::string Player;

    class ArcadeBorne : public ArcadeParse {
    public:
        ArcadeBorne(int NbArguments, char **Arguments);
        ~ArcadeBorne() = default;
        void DisplayLibs();
        void GetPlayerName();
    private:
        Player player;
    };
}