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

Arcade::menu::menu() : CurrentGame(0)
{
    GetGameLibraries();
    Images.push_back(std::make_shared<Tile>("contents/Arcade.png", ' ', BLUE, 0, 0));
    GameTile = std::make_shared<Text>(Games[CurrentGame], WHITE, 0, 1);
    GamePic = std::make_shared<Tile>("contents/arcade_pacman.png", ' ', BLUE,0,0);
    texts.push_back(std::make_shared<Text>("Hello", WHITE, 0, 0));
}

std::vector<Arcade::Object> Arcade::menu::GameLoop(Input input)
{
    std::vector<Object> objects;
    if (input == ARROW_LEFT)
        CurrentGame = Modulo(CurrentGame - 1, int (Games.size()));
    if (input == ARROW_RIGHT)
        CurrentGame = Modulo(CurrentGame + 1, int (Games.size()));
    if (input == ARROW_LEFT || input == ARROW_RIGHT) {
        GameTile.get()->setText(Games[CurrentGame]);
        SetGamePicture();
    }
    objects.push_back(GamePic);
    for (auto &Image : Images)
        objects.push_back(Image);
    for (auto &Text : texts)
        objects.push_back(Text);
    objects.push_back(GameTile);
    return objects;
}

void Arcade::menu::ResetGame()
{
    CurrentGame = 0;
    GameTile.get()->setText(Games[CurrentGame]);
    SetGamePicture();
}

void Arcade::menu::GetGameLibraries() {
    std::string LibrariesPath = "./lib";
    for (const auto &File: std::filesystem::directory_iterator(LibrariesPath))
        if (regex_search(File.path().string(), std::regex (GAME_LIB_PATTERN)))
            Games.push_back(File.path().filename().replace_extension().string());
}

int Arcade::menu::Modulo(int a, int b) {
    return (b + (a % b)) % b;
}

void Arcade::menu::SetGamePicture() {
    Game GamePicturePath = "contents/" + Games[CurrentGame] + ".png";
    std::ifstream f(GamePicturePath.c_str());
    if (f.good())
        GamePic = std::make_shared<Tile>(GamePicturePath, ' ', BLUE,0,0);
}
