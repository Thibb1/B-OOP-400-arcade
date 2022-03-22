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
        virtual ~IGame() = default;
        virtual std::vector<Object> GameLoop(Input input) = 0;
        virtual int GetScore() = 0;
        virtual void ResetGame() = 0;
    };
}