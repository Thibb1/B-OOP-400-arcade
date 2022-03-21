/*
** EPITECH PROJECT, {$CURRENT_YEAR}
** Library.cpp
** File description:
** TODO
*/

#include "Library.hpp"

Arcade::Library::Library(const LibName& libName) : handle(dlopen(libName.c_str(), RTLD_NOW | RTLD_LOCAL), [] (void *handle_ptr) { dlclose(handle_ptr);})
{
    if (!handle)
        throw ArcadeRuntimeError("Cannot open " + libName);
}
