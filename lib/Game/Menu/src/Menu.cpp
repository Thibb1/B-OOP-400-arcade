/*
** EPITECH PROJECT, 2022
** menu.cpp
** File description:
** TODO
*/

#include "Menu.hpp"

extern "C" Arcade::menu *Arcade::entry_point()
{
    return new Arcade::menu;
}

Arcade::menu::menu() : Score(0)
{
    walls.push_back(std::make_shared<Tile>("contents/img.png", 'X', BLUE, 3, 2));
    walls.push_back(std::make_shared<Tile>("contents/img.png", 'X', BLUE, 4, 2));
    walls.push_back(std::make_shared<Tile>("contents/img.png", 'X', RED, 8, 8));
}

std::vector<Arcade::Object> Arcade::menu::GameLoop(Input input)
{
    (void) input;
    std::vector<Object> objects;
    for (auto &Wall : walls)
        objects.push_back(Wall);
    return objects;
}

void Arcade::menu::ResetGame()
{
    Score = 0;
}


