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
        Library() noexcept = default;
        ~Library() noexcept {
            UnloadDisplay();
            UnloadGame();
        }
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
        void UnloadGame() noexcept {
            delete game;
            game = nullptr;
            if (GameHandle)
                dlclose(GameHandle);
            GameHandle = nullptr;
        }
        void UnloadDisplay() noexcept {
            delete display;
            display = nullptr;
            if (DisplayHandle)
                dlclose(DisplayHandle);
            DisplayHandle = nullptr;
        }
        IGame *GetGame() {return game;}
        IDisplay *GetDisplay() {return display;}
    };
}