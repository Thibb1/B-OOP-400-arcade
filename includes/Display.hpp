/*
** EPITECH PROJECT, 2022
** Display.hpp
** File description:
** Interface for Graphic Libraries
*/

#pragma once

#include <memory>

#include "Object.hpp"

namespace Arcade
{
    class IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual Input GetInput() = 0;
        virtual void ClearScreen() = 0;
        virtual void RefreshScreen() = 0;
        virtual void DrawObject(Object object) = 0;
    };
}