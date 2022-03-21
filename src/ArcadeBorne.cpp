/*
** EPITECH PROJECT, 2022
** Arcade.cpp
** File description:
** TODO
*/

#include "Arcade.hpp"
#include "ArcadeBorne.hpp"

Arcade::ArcadeBorne::ArcadeBorne(int NbArguments, char **Arguments) : ArcadeParse(NbArguments, Arguments)
{
    DisplayLibs();
    GetPlayerName();
    auto test = Library(Graphics[CurrentGraphic]);
}

void Arcade::ArcadeBorne::DisplayLibs()
{
    std::cout << "Games libraries:" << std::endl;
    for (const Game &game : Games) {
        std::cout << game << std::endl;
    }
    std::cout << "\nGraphic libraries:" << std::endl;
    for (const Graphic &graphic : Graphics) {
        std::cout << graphic << std::endl;
    }
}

void Arcade::ArcadeBorne::GetPlayerName()
{
    std::cout << "\nEnter your name: ";
    std::cin >> player;
    std::cout << "Hello " << player << "!" << std::endl;
}
