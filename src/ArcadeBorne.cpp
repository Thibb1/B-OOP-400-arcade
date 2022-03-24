/*
** EPITECH PROJECT, 2022
** Arcade.cpp
** File description:
** TODO
*/

#include "ArcadeBorne.hpp"

using namespace std::chrono_literals;

Arcade::ArcadeBorne::ArcadeBorne(int NbArguments, char **Arguments) : ArcadeParse(NbArguments, Arguments)
{
    DisplayLibs();
    GetPlayerName();
    libraries.LoadGame("./lib/arcade_Menu.so");
    LoadGraphicLib();
    while (true) {
        Input input = libraries.GetDisplay()->GetInput();
        switch (input) {
            case EXIT:
                return;
            case N:
                CurrentGraphic = (CurrentGraphic + 1) % int (Graphics.size());
                LoadGraphicLib();
                break;
            case P:
                CurrentGraphic = (CurrentGraphic - 1) & int (Graphics.size() - 1);
                LoadGraphicLib();
                break;
            case F:
                CurrentGame = (CurrentGame + 1) % int (Games.size());
                LoadGameLib();
                break;
            case B:
                CurrentGame = (CurrentGame - 1) & int (Games.size() - 1);
                LoadGameLib();
                break;
            case M:
                libraries.LoadGame("./lib/arcade_Menu.so");
                break;
            case R:
                libraries.GetGame()->ResetGame();
                break;
            default:
                libraries.GetDisplay()->ClearScreen();
                libraries.GetGame()->GetScore();
                auto objects = libraries.GetGame()->GameLoop(input);
                if (!objects.empty()) {
                    for (auto &object: objects)
                        libraries.GetDisplay()->DrawObject(object);
                }
                libraries.GetDisplay()->RefreshScreen();
                break;
        }
        std::this_thread::sleep_for(6000us);
    }
}

void Arcade::ArcadeBorne::DisplayLibs()
{
    std::cout << "Games libraries:" << std::endl;
    for (const Game &GameLibrary : Games) {
        std::cout << GameLibrary << std::endl;
    }
    std::cout << "\nGraphic libraries:" << std::endl;
    for (const Graphic &GraphicLibrary : Graphics) {
        std::cout << GraphicLibrary << std::endl;
    }
}

void Arcade::ArcadeBorne::GetPlayerName()
{
    std::cout << "\nEnter your name: ";
    std::cin >> player;
    std::cout << "Hello " << player << "!" << std::endl;
}

void Arcade::ArcadeBorne::LoadGraphicLib()
{
   libraries.LoadDisplay(Graphics[CurrentGraphic]);
}

void Arcade::ArcadeBorne::LoadGameLib()
{
    libraries.LoadGame(Games[CurrentGame]);
}
