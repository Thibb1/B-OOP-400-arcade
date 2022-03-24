/*
** EPITECH PROJECT, 2022
** menu.hpp
** File description:
** TODO
*/

#pragma once

#include "Game.hpp"

#include <regex>
#include <filesystem>

#include "ArcadeError.hpp"

#define GAME_LIB_PATTERN R"(lib\/arcade_(nibbler|pacman|qix|centiped|solarfox)\.so$)"


namespace Arcade
{
    typedef std::string Game;
    typedef std::shared_ptr<Text> TextObject;

    class menu : public IGame {
    private:
        int Score;
        int CurrentGame;
        std::vector<Object> Images;
        TextObject GameTile;
        Object GamePic;
        std::vector<Object> texts;
        std::vector<Game> Games;
        std::vector<Object> tiles;
    public:
        menu();
        ~menu() override = default;
        void GetGameLibraries();
        std::vector<Object> GameLoop(Input input) override;
        int GetScore() override {return Score;}
        void ResetGame() override;
    };
    extern "C" menu *entry_point();
}