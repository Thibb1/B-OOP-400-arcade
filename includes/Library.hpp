/*
** EPITECH PROJECT, 2022
** Library.hpp
** File description:
** TODO
*/

#pragma once

#include <memory>
#include <string>
#include <dlfcn.h>

#include "ArcadeError.hpp"
#include "Display.hpp"
#include "Game.hpp"

typedef std::string LibName;
namespace Arcade
{
    class Library {
    private:
        void *GameHandle = nullptr;
        void *DisplayHandle = nullptr;
        IGame *game = nullptr;
        IDisplay *display = nullptr;

    public:
        /**
         * The default constructor for the Library class
         */
        Library() noexcept = default;

        /**
         * This function is called when the object is destroyed
         */
        ~Library() noexcept {
            UnloadDisplay();
            UnloadGame();
        }

        /**
         * Loads the game and returns a pointer to the game's entry point
         *
         * @param GameName The name of the game to load.
         */
        void LoadGame(const LibName& GameName) {
            UnloadGame();
            GameHandle = dlopen(GameName.c_str(), RTLD_NOW);
            if (!GameHandle)
                throw Arcade::ArcadeRuntimeError(dlerror());
            dlerror();
            void *EntryPoint = dlsym(GameHandle, "entry_point");
            if (!EntryPoint)
                throw Arcade::ArcadeRuntimeError(dlerror());
            game = reinterpret_cast<IGame *(*)()>(EntryPoint)();
        }

        /**
         * Loads the display library and returns a pointer to the display object
         *
         * @param DisplayName The name of the display library.
         */
        void LoadDisplay(const LibName& DisplayName) {
            UnloadDisplay();
            DisplayHandle = dlopen(DisplayName.c_str(), RTLD_NOW);
            if (!DisplayHandle)
                throw Arcade::ArcadeRuntimeError(dlerror());
            dlerror();
            void *EntryPoint = dlsym(DisplayHandle, "entry_point");
            if (!EntryPoint)
                throw Arcade::ArcadeRuntimeError(dlerror());
            display = reinterpret_cast<IDisplay *(*)()>(EntryPoint)();
        }

        /**
         * It deletes the game object and closes the game's dynamic library
         */
        void UnloadGame() noexcept {
            delete game;
            game = nullptr;
            if (GameHandle)
                dlclose(GameHandle);
            GameHandle = nullptr;
        }

        /**
         * The function deletes the display object and closes the display library
         */
        void UnloadDisplay() noexcept {
            delete display;
            display = nullptr;
            if (DisplayHandle)
                dlclose(DisplayHandle);
            DisplayHandle = nullptr;
        }

        /**
         * Get the game object.
         *
         * @return The game object.
         */
        IGame *GetGame() {return game;}

        /**
         * Get the display object.
         *
         * @return The display object.
         */
        IDisplay *GetDisplay() {return display;}
    };
}