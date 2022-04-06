/*
** EPITECH PROJECT, 2022
** Game.hpp
** File description:
** Interface for Game Libraries
*/

#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"

namespace Arcade
{
    class IGame {
    public:
        /**
         * This is the destructor
         */
        virtual ~IGame() = default;

        /**
         * Telling the compiler that the function GameLoop is virtual and has a return type of std::vector<Object>.
         */
        virtual std::vector<Object> GameLoop(Input input) = 0;

        /**
         * Telling the compiler that the function GetScore is virtual and has a return type of int.
         */
        virtual int GetScore() = 0;

        /**
         * Telling the compiler that the function ResetGame is virtual and has a return type of void.
         */
        virtual void ResetGame() = 0;
    };
}