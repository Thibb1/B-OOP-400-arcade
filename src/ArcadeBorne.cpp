/*
** EPITECH PROJECT, 2022
** Arcade.cpp
** File description:
** TODO
*/

#include "ArcadeBorne.hpp"

using namespace std::chrono_literals;

Arcade::ArcadeBorne::ArcadeBorne(int NbArguments, char **Arguments) : ArcadeParse(NbArguments, Arguments), InMenu(true)
{
    DisplayLibs();
    GetPlayerName();
    LoadGraphicLib();
    libraries.LoadGame("./lib/arcade_Menu.so");
    while (true) {
        Input input = libraries.GetDisplay()->GetInput();
        switch (input) {
            case ENTER:
                if (!InMenu)
                    break;
                CurrentGame = libraries.GetGame()->GetScore();
                LoadGameLib();
                InMenu = false;
                break;
            case EXIT:
                if (!InMenu)
                    SaveScore();
                libraries.UnloadDisplay();
                libraries.UnloadGame();
                return;
            case N:
                CurrentGraphic = Modulo(CurrentGraphic + 1, int (Graphics.size()));
                LoadGraphicLib();
                break;
            case P:
                CurrentGraphic = Modulo(CurrentGraphic - 1, int (Graphics.size()));
                LoadGraphicLib();
                break;
            case F:
                CurrentGame = Modulo(CurrentGame + 1, int (Games.size()));
                LoadGameLib();
                break;
            case B:
                CurrentGame = Modulo(CurrentGame - 1, int (Games.size()));
                LoadGameLib();
                break;
            case M:
                if (InMenu)
                    break;
                SaveScore();
                InMenu = true;
                libraries.LoadGame("./lib/arcade_Menu.so");
                break;
            case R:
                if (!InMenu)
                    SaveScore();
                libraries.GetGame()->ResetGame();
                break;
            default:
                libraries.GetDisplay()->ClearScreen();
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
    player = std::regex_replace(player, std::regex (R"([^\w]*(\w*).*)"),"$1");
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

int Arcade::ArcadeBorne::Modulo(int a, int b) {
    return (b + (a % b)) % b;
}

void Arcade::ArcadeBorne::SaveScore() {
    auto score = libraries.GetGame()->GetScore();
    std::ofstream Score("./scores/game"+ std::to_string(CurrentGame) + ".txt");
    if (!Score.is_open())
        throw ArcadeRuntimeError("Cannot open score file");
    Score << player + "|" << score << std::endl;
}
