/*
** EPITECH PROJECT, 2022
** ncurses.cpp
** File description:
** TODO
*/

#include "ncurses.hpp"

extern "C" Arcade::ncurses *Arcade::entry_point()
{
    return new Arcade::ncurses;
}

Arcade::ncurses::ncurses()
{
    setlocale(LC_ALL, "");
    initscr();
    if (isendwin()) {
        newterm(std::getenv("TERM"), stdin, stdout);
        endwin();
        initscr();
    }

    start_color();
    noecho();
    use_default_colors();
    set_escdelay(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);
    for (int i = 0; i < COLORS; i++)
        init_extended_pair(i + 1, i, -1);
}

void Arcade::ncurses::RefreshScreen()
{
    if (!isendwin())
        wrefresh(stdscr);
    else
        initscr();
}

Arcade::Input Arcade::ncurses::GetInput()
{
    Input InputUser = NOTHING;
    if (isendwin())
        return EXIT;
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
        else if (ch == 32)
            InputUser = SPACE;
        else if (ch == 27)
            InputUser = EXIT;
        ch = getch();
    }
    return InputUser;
}

void Arcade::ncurses::ClearScreen()
{
    wclear(stdscr);
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
    int color = pText->getColor();
    attron(COLOR_PAIR(color));
    mvprintw(int (pText->getPosition().second), int (pText->getPosition().first), pText->getText().c_str());
    attroff(COLOR_PAIR(color));
}

void Arcade::ncurses::DrawTile(Arcade::Tile *Tile)
{
    int color = Tile->getColor();
    attron(COLOR_PAIR(color));
    mvprintw(int(Tile->getPosition().second), int(Tile->getPosition().first), Tile->getCharacter().c_str());
    attroff(COLOR_PAIR(color));
    Path path = Tile->getTexturePath()+"_compressed.png";
    std::fstream file(path);
    if (file.good()) {
        Converter conv(Tile->getTexturePath() + "_compressed.png");
        conv.processImage(Tile->getPosition());
    }
}


Arcade::ncurses::~ncurses()
{
    clear();
    refresh();
    endwin();
    std::cerr << "Deleted" << std::endl;
}

void Converter::processImage(Arcade::Position position) {
    if (!rows)
        return;
    for (float yIdx = 0; uint (yIdx) < height; yIdx += 1 * yFactor) {
        for (float xIdx = 0; uint (xIdx) < width; xIdx += 1 * xFactor) {
            int x = int (xIdx);
            int y = int (yIdx);
            int r = rows[y][x * 4 + 0];
            int g = rows[y][x * 4 + 1];
            int b = rows[y][x * 4 + 2];
            int alpha = rows[y][x * 4 + 3];
            if (alpha < 180)
                continue;
            int Color = 0;
            int SmallestColorDiff = 1000;
            for (int i = 0; i < COLORS; i++) {
                Pixel p;
                extended_color_content(i, &p.r, &p.g, &p.b);
                p.ConvertPixel();
                int ColorDiff = abs(p.r - r) + abs(p.g - g) + abs(p.b - b);
                if (ColorDiff < SmallestColorDiff) {
                    Color = i;
                    SmallestColorDiff = ColorDiff;
                }
            }
            attron(COLOR_PAIR(Color));
            mvprintw(int (position.second) + int (yIdx / yFactor), int (position.first) + int (xIdx / xFactor), "█");
            attroff(COLOR_PAIR(Color));
        }
    }
}
