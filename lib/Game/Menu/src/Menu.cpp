/*
** EPITECH PROJECT, 2022
** menu.cpp
** File description:
** TODO
*/

#include "Menu.hpp"

extern "C" Arcade::menu *Arcade::entry_point()
{
    return new Arcade::menu;
}

Arcade::menu::menu() : Score(0), CurrentGame(0)
{
    GetGameLibraries();
    Images.push_back(std::make_shared<Tile>("contents/Arcade.png", 'X', BLUE, 0, 0));
    GameTile = std::make_shared<Text>(Games[CurrentGame], WHITE, 0, 1);
    //GamePic = std::make_shared<Tile>("")
    texts.push_back(std::make_shared<Text>("Hello", WHITE, 5, 5));
}

std::vector<Arcade::Object> Arcade::menu::GameLoop(Input input)
{
    std::vector<Object> objects;
    if (input == ARROW_LEFT)
        CurrentGame = (CurrentGame - 1) & int (Games.size() - 1);
    if (input == ARROW_RIGHT)
        CurrentGame = (CurrentGame + 1) % int (Games.size());
    if (input == ARROW_LEFT || input == ARROW_RIGHT) {
        GameTile.get()->setText(Games[CurrentGame]);
    }
    for (auto &Image : Images)
        objects.push_back(Image);
    for (auto &Text : texts)
        objects.push_back(Text);
    objects.push_back(GameTile);
    return objects;
}

void Arcade::menu::ResetGame()
{
    Score = 0;
    CurrentGame = 0;
}

void Arcade::menu::GetGameLibraries() {
    std::string LibrariesPath = "./lib";
    for (const auto &File: std::filesystem::directory_iterator(LibrariesPath))
        if (regex_search(File.path().string(), std::regex (GAME_LIB_PATTERN)))
            Games.push_back(File.path().filename().string());
}
