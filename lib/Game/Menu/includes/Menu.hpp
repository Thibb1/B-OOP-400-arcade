/*
** EPITECH PROJECT, 2022
** menu.hpp
** File description:
** TODO
*/

#pragma once

#include "Game.hpp"
#include "ArcadeError.hpp"

namespace Arcade
{
    class menu : public IGame {
    private:
        int Score;
        std::vector<Object> walls;
    public:
        menu();
        ~menu() override = default;
        std::vector<Object> GameLoop(Input input) override;
        int GetScore() override {return Score;}
        void ResetGame() override;
    };
    extern "C" menu *entry_point();
}