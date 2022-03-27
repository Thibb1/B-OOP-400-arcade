/*
** EPITECH PROJECT, 2022
** Nibbler.cpp
** File description:
** TODO
*/

#include "Nibbler.hpp"

extern "C" Arcade::Nibbler *Arcade::entry_point()
{
    return new Arcade::Nibbler;
}

Arcade::Nibbler::Nibbler()
{
    /*GENERATION MAP & SOUND (SDL2/SFML)*/

}

void Arcade::Nibbler::ResetNibbler()
{
    /* COPIE DU CONSTRUCTEUR*/
    NibblerFruitGeneration();
}

void Arcade::Nibbler::NibblerFruitGeneration()
{
    int fruit = 0;

    for (; map[fruit] != ' '; fruit++);                   /* map c'est la string contenant la map*/
    map[fruit] = NibblerFruit;
 }

 std::vector<std::shared_ptr<Arcade::IObject>> Arcade::Nibbler::GameLoop(Arcade::Input input)
 {
    int CheckSnake = CheckMovement()
    if (GetInput::Right/*J ai voulu mettre le GetInput mais marche pas jsp */) {
        x_skake = 1;
        y_snake = 0;
    } else if (GetInput::Left) {
        x_skake = -1;
        y_snake = 0;
    } else if (GetInput::Up) {
        x_skake = 0;
        y_snake = -1;
    } else if (GetInput::Left) {
        x_skake = 0;
        y_snake = 1;
    }
    if (CheckMovement() == 84)
        NibblerGameOver();
    /*print le mouvement*/
 }

/*std::vector<std::shared_ptr<Arcade::IObject>>*/ void NibblerGameOver(void)
{
    /*wprintf("press R for restart");
    wprintf("press M for menu");            c 'est le gameover mais que en ncurses)
    wprintf("press R for restart");*/
}


 int Arcade::Nibbler::CheckMovement()
 {
    if (map[/*pos_nibbler*/] == NibblerWall || map[/*pos_nibbler*/] == Nibblertail)
        return 84;
    else if (map[/*pos_nibbler] == NibblerFruit) {
        NibblerFruitGeneration()
        /*add 1 size of NibblerTail*/
    }
    else {
        /*Nibbler continue playing*/
    }
 }



