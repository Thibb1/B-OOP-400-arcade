/*
** EPITECH PROJECT, 2022
** sdl2.hpp
** File description:
** TODO
*/

#pragma once

#include "Display.hpp"
#include "Object.hpp"
#include <map>
#include <ncurses.h>
#include <curses.h>

#include "ArcadeError.hpp"


namespace Arcade
{
    class ncurses: public IDisplay {
    private:
    public:
        ncurses();
        ~ncurses() override;
        Input GetInput() override;
        void ClearScreen() override;
        void RefreshScreen() override;
        void DrawObject(Object object) override;
        static void DrawTile(Tile *Tile);

        static void DrawText(Text *pText);
    };
    extern "C" ncurses *entry_point();
}