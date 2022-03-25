/*
** EPITECH PROJECT, 2022
** ncurses.cpp
** File description:
** TODO
*/

#include "ncurses.hpp"
#include <ncurses.h>
#include <curses.h>

extern "C" Arcade::ncurses *Arcade::entry_point()
{
    return new Arcade::ncurses;
}

Arcade::ncurses::ncurses()
{
    initscr();
}

void Arcade::ncurses::RefreshScreen()
{
    refresh();
}

Arcade::Input Arcade::ncurses::GetInput()
{
    auto InputUser = static_cast<Input>(NULL);
    int ch = getch();

    while (ch != KEY_F(2)) {
        ch = getch();
        if (ch == KEY_LEFT)
            InputUser = ARROW_LEFT;
        else if (ch == KEY_RIGHT)
            InputUser = ARROW_RIGHT;
        else if (ch == KEY_UP)
            InputUser = ARROW_UP;
        else if (ch == KEY_DOWN)
            InputUser = ARROW_DOWN;
        else if (ch == 78 || ch == 110)
            InputUser = N;
        else if (ch == 80 || ch == 112)
            InputUser = P;
        else if (ch == 70 || ch == 102)
            InputUser = F;
        else if (ch == 98 || ch == 66)
            InputUser = B;
        else if (ch == 77 || ch == 109)
            InputUser = M;
        else if (ch == 114 || ch == 82)
            InputUser = R;
        else if (ch == KEY_ENTER)
            InputUser = ENTER;
        else if (ch == KEY_EXIT)
            InputUser = EXIT;
    }
    return InputUser;
}

void Arcade::ncurses::ClearScreen()
{
    clear();
}

void Arcade::ncurses::DrawObject(Arcade::Object object)
{
    /*auto Tile = dynamic_cast<Arcade::Tile *>(object.get());
    if (Tile)
        DrawTile(Tile);
    auto Text = dynamic_cast<Arcade::Text *>(object.get());
    if (Text)
        DrawText(Text);*/
}

void Arcade::ncurses::DrawText(Arcade::Text *pText)
{

}

void Arcade::ncurses::DrawTile(Arcade::Tile *Tile)
{

}


Arcade::ncurses::~ncurses()
{
    dprintf(2, "world\n");
    endwin();
}
