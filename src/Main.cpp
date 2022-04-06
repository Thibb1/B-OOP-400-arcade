/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** main
*/

#include "Arcade.hpp"

static void callHandler(int sig) {(void) sig;}

int main(int NbArguments, char **Arguments)
{
    signal(SIGINT, callHandler);
    try {
        Arcade::ArcadeBorne borne(NbArguments, Arguments);
    } catch (Arcade::ArcadeError &Error) {
        // std::cerr << Error.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::exception &Error) {
        // std::cerr << Error.what() << std::endl;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
