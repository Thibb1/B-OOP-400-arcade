/*
** EPITECH PROJECT, {$CURRENT_YEAR}
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
    typedef std::unique_ptr<void, void (*) (void *)> Handle;
    typedef std::string LibName;
    //template<typename Lib>
    class Library {
    private:
        Handle handle;
    public:
        Library(const LibName& libName);
        virtual ~Library() = default;
    };
}