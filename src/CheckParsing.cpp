/*
** EPITECH PROJECT, 2022
** CheckParsing.cpp
** File description:
** TODO
*/

#include <thread>
#include <iostream>
#include <chrono>
#include <regex>

bool check_error(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << av [0] << ": USAGE: "<< av[0] << " ./lib/arcade_(sfml|sdl2|ncurses).so" << std::endl;
        return false;
    }
    return true;
}

void test_regex(char *file_name)
{
    std::regex reg(R"(lib\/arcade_(ndk\+\+|aalib|ncurses|sdl2|libcaca|allegro5|xlib|gtk\+|sfml|irrlicht|opengl|vulkan|qt5)\.so$)");
    if (regex_search(file_name, reg))
        std::cout << "matched" << std::endl;
    else
        std::cout << "not matched" << std::endl;
}

