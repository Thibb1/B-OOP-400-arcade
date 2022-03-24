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
            if (GameHandle)
                dlclose(GameHandle);
            if (DisplayHandle)
                dlclose(DisplayHandle);
            game = nullptr;
            display = nullptr;
            GameHandle = nullptr;
            DisplayHandle = nullptr;
        }
        void LoadGame(const LibName& GameName) {
            if (GameHandle)
                dlclose(GameHandle);
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
            if (DisplayHandle)
                dlclose(GameHandle);
            DisplayHandle = dlopen(DisplayName.c_str(), RTLD_NOW);
            if (!DisplayHandle)
                throw Arcade::ArcadeRuntimeError(dlerror());
            dlerror();
            void *EntryPoint = dlsym(DisplayHandle, "entry_point");
            if (!EntryPoint)
                throw Arcade::ArcadeRuntimeError(dlerror());
            display = reinterpret_cast<IDisplay *(*)()>(EntryPoint)();
        }
        IGame *GetGame() {return game;}
        IDisplay *GetDisplay() {return display;}
    };
}