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
#include <fstream>

#include "ArcadeError.hpp"

#define GAME_LIB_PATTERN R"(lib\/arcade_(nibbler|pacman|qix|centiped|solarfox)\.so$)"


namespace Arcade
{
    typedef std::string Game;
    typedef std::shared_ptr<Text> TextObject;

    class menu : public IGame {
    private:
        int CurrentGame;
        std::vector<Object> Images;
        Object GamePic;
        std::vector<Object> texts;
        std::vector<Game> Games;
        std::vector<Object> tiles;
    public:
        /**
         * Creating a new object of type `menu` and initializing it.
         */
        menu();

        /**
         * The destructor for the menu class
         */
        ~menu() override = default;

        /**
         * Getting the game libraries from the `lib` folder.
         */
        void GetGameLibraries();

        /**
         * Returning a vector of objects.
         */
        std::vector<Object> GameLoop(Input input) override;

        /**
         * Get the score of the current game.
         *
         * @return The score of the current game.
         */
        int GetScore() override {return CurrentGame;}

        /**
         * Resetting the game.
         */
        void ResetGame() override;

        /**
         * A function that returns the remainder of a division.
         */
        static int Modulo(int a, int b);

        /**
         * Setting the game picture.
         */
        void SetGamePicture();
    };
    extern "C" menu *entry_point();
}