/*
** EPITECH PROJECT, 2022
** Display.hpp
** File description:
** Interface for Graphic Libraries
*/

#pragma once

#include <memory>
#include <filesystem>

#include "Object.hpp"

namespace Arcade
{
    class IDisplay {
    public:
        /**
         * This is the destructor
         */
        virtual ~IDisplay() = default;

        /**
         * Telling the compiler that the function GetInput() is virtual and has no implementation.
         */
        virtual Input GetInput() = 0;

        /**
         * Telling the compiler that the function ClearScreen() is virtual and has no implementation.
         */
        virtual void ClearScreen() = 0;

        /**
         * Telling the compiler that the function RefreshScreen() is virtual and has no implementation.
         */
        virtual void RefreshScreen() = 0;

        /**
         * Telling the compiler that the function DrawObject() is virtual and has no implementation.
         */
        virtual void DrawObject(Object object) = 0;
    };
}