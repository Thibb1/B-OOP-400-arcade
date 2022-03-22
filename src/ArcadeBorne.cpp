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
    game = LibraryGame("./lib/arcade_Menu.so");
    LoadGraphicLib();
    while (true) {
        Input input = display.GetLibrary()->GetInput();
        switch (input) {
            case EXIT:
                return;
            case N:
                CurrentGraphic = (CurrentGraphic + 1) % int (Graphics.size());
                LoadGraphicLib();
                break;
            case P:
                CurrentGraphic = (CurrentGraphic - 1) % int (Graphics.size());
                LoadGraphicLib();
                break;
            case F:
                CurrentGame = (CurrentGame + 1) % int (Games.size());
                LoadGameLib();
                break;
            case B:
                CurrentGame = (CurrentGame - 1) % int (Games.size());
                LoadGameLib();
                break;
            case M:
                game = LibraryGame("./lib/arcade_Menu.so");
                break;
            case R:
                game.GetLibrary()->ResetGame();
                break;
            default:
                display.GetLibrary()->ClearScreen();
                game.GetLibrary()->GetScore();
                auto objects = game.GetLibrary()->GameLoop(input);
                if (!objects.empty()) {
                    for (auto &object: objects)
                        display.GetLibrary()->DrawObject(object);
                }
                display.GetLibrary()->RefreshScreen();
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
    display = LibraryDisplay(Graphics[CurrentGraphic]);
}

void Arcade::ArcadeBorne::LoadGameLib()
{
    game = LibraryGame (Games[CurrentGame]);
}
