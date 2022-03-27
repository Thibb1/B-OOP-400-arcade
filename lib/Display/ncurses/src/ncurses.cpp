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
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);
    start_color();
}

void Arcade::ncurses::RefreshScreen()
{
    refresh();
}

Arcade::Input Arcade::ncurses::GetInput()
{
    Input InputUser = NOTHING;
    int ch = getch();

    while (ch != ERR) {
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
        else if (ch == 10)
            InputUser = ENTER;
        else if (ch == 27)
            InputUser = EXIT;
        ch = getch();
    }
    return InputUser;
}

void Arcade::ncurses::ClearScreen()
{
    clear();
}

void Arcade::ncurses::DrawObject(Arcade::Object object)
{
    auto Tile = dynamic_cast<Arcade::Tile *>(object.get());
    if (Tile)
        DrawTile(Tile);
    auto Text = dynamic_cast<Arcade::Text *>(object.get());
    if (Text)
        DrawText(Text);
}

void Arcade::ncurses::DrawText(Arcade::Text *pText)
{
    std::cout << pText->getText() << std::endl;
    mvprintw(int (pText->getPosition().second), int (pText->getPosition().first), pText->getText().c_str());
}

void Arcade::ncurses::DrawTile(Arcade::Tile *Tile)
{
    char character[2];
    character[0] = static_cast<char>(Tile->getCharacter());
    character[1] = '\0';
    mvprintw(int (Tile->getPosition().second), int (Tile->getPosition().first), character);
}


Arcade::ncurses::~ncurses()
{
    echo();
    curs_set(1);
    keypad(stdscr, false);
    nodelay(stdscr, false);
    nocbreak();
    endwin();
}
