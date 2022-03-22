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

namespace Arcade
{
    typedef std::string LibName;
    template<typename Lib>
    class Library {
    private:
        void *handle = nullptr;
        Lib *library = nullptr;
    public:
        Library() noexcept = default;
        ~Library() noexcept {
            if (handle)
                dlclose(handle);
            library = nullptr;
            handle = nullptr;
        }
        explicit Library(const LibName& libName) : handle(dlopen(libName.c_str(), RTLD_NOW | RTLD_LOCAL)){
            if (!handle)
                throw ArcadeRuntimeError(dlerror());
            auto EntryPoint = dlsym(handle, "entry_point");
            if (!EntryPoint)
                throw ArcadeRuntimeError(dlerror());
            library = reinterpret_cast<Lib *(*)()>(EntryPoint)();
        }
        Lib *GetLibrary() {
            return library;
        }
    };
}