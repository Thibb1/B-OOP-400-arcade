/*
** EPITECH PROJECT, 2022
** ArcadeParse.cpp
** File description:
** TODO
*/

#include "Arcade.hpp"

Arcade::ArcadeParse::ArcadeParse(int NbArguments, char **Arguments) : CurrentGame(0)
{
    CheckArgument(NbArguments, Arguments);
    GetLibraries();
    CheckLibraries();
    CurrentGraphic = int (std::distance(Graphics.begin(), std::find(Graphics.begin(), Graphics.end(), Arguments[1]))) % int (Graphics.size());
}


void Arcade::ArcadeParse::CheckArgument(int NbArguments, char **Arguments)
{
    std::regex GraphicLibraryPattern(GRAPHIC_LIB_PATTERN);

    if (NbArguments != 2)
        throw ArcadeUsageError();
    if (!regex_search(Arguments[1], GraphicLibraryPattern))
        throw ArcadeUsageError();
}

void Arcade::ArcadeParse::GetLibraries()
{
    std::string LibrariesPath = "./lib";
    std::regex GraphicLibraryPattern(GRAPHIC_LIB_PATTERN);
    std::regex GameLibraryPattern(GAME_LIB_PATTERN);

    for (const auto &File: std::filesystem::directory_iterator(LibrariesPath)) {
        if (regex_search(File.path().string(), GraphicLibraryPattern))
            Graphics.push_back(File.path().string());
        else if (regex_search(File.path().string(), GameLibraryPattern))
            Games.push_back(File.path().string());
    }
}

void Arcade::ArcadeParse::CheckLibraries()
{
    if (Graphics.empty())
        throw ArcadeMissingError("Graphic library");
    if (Games.empty())
        throw ArcadeMissingError("Game library");
}
