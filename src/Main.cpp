/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** main
*/

#include "Arcade.hpp"

int main(int NbArguments, char **Arguments)
{
    try {
        Arcade::ArcadeBorne(NbArguments, Arguments);
    } catch (Arcade::ArcadeError &Error) {
        std::cerr << Error.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::exception &Error) {
        std::cerr << Error.what() << std::endl;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
