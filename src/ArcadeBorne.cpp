/*
** EPITECH PROJECT, 2022
** Arcade.cpp
** File description:
** Borne arcade
*/

#include "ArcadeBorne.hpp"

using namespace std::chrono_literals;

Arcade::ArcadeBorne::ArcadeBorne(int NbArguments, char **Arguments) : ArcadeParse(NbArguments, Arguments), InMenu(true), lastVectorHash(0)
{
    DisplayLibs();
    DisplayScores();
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
                InMenu = false;
                SaveScore();
                CurrentGame = Modulo(CurrentGame + 1, int (Games.size()));
                LoadGameLib();
                break;
            case B:
                InMenu = false;
                SaveScore();
                CurrentGame = Modulo(CurrentGame - 1, int (Games.size()));
                LoadGameLib();
                break;
            case M:
                SaveScore();
                InMenu = true;
                libraries.LoadGame("./lib/arcade_Menu.so");
                break;
            case R:
                SaveScore();
                libraries.GetGame()->ResetGame();
                break;
            default:
                auto objects = libraries.GetGame()->GameLoop(input);
                if (HashVector(objects) != lastVectorHash) {
                    libraries.GetDisplay()->ClearScreen();
                    if (!objects.empty()) {
                        for (auto &object: objects)
                            libraries.GetDisplay()->DrawObject(object);
                    }
                    libraries.GetDisplay()->RefreshScreen();
                    lastVectorHash = HashVector(objects);
                }
                break;
        }
        std::this_thread::sleep_for(6000us);
    }
}
size_t Arcade::ArcadeBorne::HashVector(const Arcade::VObjs& vec) {
    std::size_t seed = vec.size();
    for(auto& i : vec) {
        auto ptr_ref= std::hash<IObject *>()(i.get());
        auto Tile = dynamic_cast<Arcade::Tile *>(i.get());
        if (Tile) {
            auto pos = Tile->getPosition();
            auto posRef = std::hash<float>()(pos.first);
            posRef ^= std::hash<float>()(pos.second);
            seed ^= posRef + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        seed ^= ptr_ref + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
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
}

void Arcade::ArcadeBorne::LoadGraphicLib()
{
    lastVectorHash = 0;
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
    if (InMenu)
        return;
    auto score = libraries.GetGame()->GetScore();
    std::ofstream Score("./scores/game"+ std::to_string(CurrentGame) + ".txt", std::ios_base::app);
    if (!Score.is_open())
        throw ArcadeRuntimeError("Cannot open score file");
    Score << player + "|" << score << std::endl;
}

void Arcade::ArcadeBorne::DisplayScores() {
    for (int i = 0; i < int (Games.size()); i++) {
        std::string path = "scores/game" + std::to_string(i) + ".txt";
        if (std::filesystem::exists(path)) {
            std::cout << "\nHigh-scores for " << Games[i] << ":";
            std::vector<std::pair<int, std::string>> Scores;
            std::fstream file(path);
            std::string line;
            while (getline(file, line)) {
                std::stringstream ss(line);
                std::string name;
                getline(ss, name, '|');
                std::string item;
                getline(ss, item, '|');
                int score = std::stoi(item);
                if (score < 1)
                    continue;
                Scores.emplace_back(score, name);
            }
            std::sort(Scores.rbegin(), Scores.rend());
            for (const auto& item: Scores)
                std::cout << "\n" + item.second << ": " << item.first;
            std::cout << std::endl;
        }

    }
}
