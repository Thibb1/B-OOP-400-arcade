/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** TODO
*/

#pragma once

#include <string>
#include <thread>
#include <fstream>

#include "ArcadeParse.hpp"
#include "Library.hpp"
#include "Display.hpp"
#include "Game.hpp"

namespace Arcade
{
    typedef std::string Player;
    typedef std::vector<Object> VObjs;

    class ArcadeBorne : public ArcadeParse {
    public:
        /**
         * The constructor of the class. It is called when the object is created.
         * @param NbArguments The number of arguments given to the program.
         * @param Arguments The arguments given to the program.
         */
        ArcadeBorne(int NbArguments, char **Arguments);
        /**
         * The destructor is a special function that is called when an object is
         * destroyed
         */
        ~ArcadeBorne() = default;

        /**
         * Displaying the list of available libraries.
         */
        void DisplayLibs();

        /**
         * Asking the player to enter his name.
         */
        void GetPlayerName();

        /**
         * It loads the graphic library.
         */
        void LoadGraphicLib();

        /**
         * It loads the game library.
         */
        void LoadGameLib();

        /**
         * A function that returns the remainder of the division of the first argument by the second.
         * @param a The first argument.
         * @param b The second argument.
         */
        static int Modulo(int a, int b);

        /**
         * A function that hashes the vector of objects.
         * @param v The vector of objects.
         */
        static size_t HashVector(const VObjs& vec);
    private:
        Player player;
        Library libraries;
        bool InMenu;
        size_t lastVectorHash;
        void SaveScore();

        void DisplayScores();
    };
}