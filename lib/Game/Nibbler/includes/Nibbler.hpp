/*
** EPITECH PROJECT, 2022
** Nibbler.hpp
** File description:
** TODO
*/

#include <random>
#include <memory>
#include "Game.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include "Display.hpp"

#define ARCADE_NIBBLER_H
#ifndef ARCADE_NIBBLER_H


namespace Arcade {

    class Nibbler : public IGame {

    private:
        char NibblerHead = "S";
        char NibblerTail = "s";
        char NibblerFruit = "*";
        char NibblerWall =  "#";
        int x_snak;
        int y_snak;
        int count_nibbler;
    public:
        Nibbler();
        ~Nibbler() = default:
        std::vector<std::shared_ptr<Arcade::IObject>> GameLoop(Arcade::Input input) override;
        void ResetNibbler();
        void NibblerFruitGeneration();
    };
    extern "C" Nibbler *entry_point();
}



#endif //ARCADE_NIBBLER_H
