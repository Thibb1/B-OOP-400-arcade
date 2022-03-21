/*
** EPITECH PROJECT, 2022
** Display.hpp
** File description:
** TODO
*/

#pragma once

#include <memory>
#include "Object.hpp"

namespace Arcade
{
    enum Input {LEFT_ARROW, RIGHT_ARROW, UP_ARROW, DOWN_ARROW};
    typedef IObject Object;
    class IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual Arcade::IDisplay LastInput() = 0;
        virtual void ClearScreen() = 0;
        virtual void RefreshScreen() = 0;
        virtual void DrawObject(std::shared_ptr<Object>) = 0;
    };
}