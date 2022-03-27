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

Arcade::Nibbler::Nibbler() : position(5, 5), Direction(ARROW_LEFT), Score(0), Size(3)
{
    std::fstream WallsFile("contents/Nibbler.txt");
    std::string Line;
    int y = 0;
    if (!WallsFile.is_open())
        throw ArcadeMissingError("contents/Nibbler.txt");
    while (std::getline(WallsFile, Line)) {
        for (int x = 0; x < int (Line.size()); x++) {
            if (Line[x] == WALL)
                Walls.push_back(std::make_shared<Tile>("contents/wall.png", WALL, BLUE,x,y));
        }
        y++;
    }
    SnakeHead = std::make_shared<Tile>("contents/SnakeHead.png", HEAD, BLUE, position.first, position.second);
    SnakeHead->setRotation(180);
    for (int x = 1; x <= Size; x++)
        SnakeBody.push_back(std::make_shared<Tile>("contents/SnakeBody.png", TAIL, BLUE,position.first + float (x),position.second));
}

void Arcade::Nibbler::ResetGame()
{
    Score = 0;
    position = {5, 5};
    Direction = ARROW_LEFT;
    Size = 4;
    NibblerFruitGeneration();
}

void Arcade::Nibbler::NibblerFruitGeneration()
{
    //int fruit = 0;

    //for (; map[fruit] != ' '; fruit++);                   /* map c'est la string contenant la map*/
    //map[fruit] = NibblerFruit;
}

 std::vector<Arcade::Object> Arcade::Nibbler::GameLoop(Input input)
{
    std::vector<Object> objects;
    SnakeHead->setPosition(position);
    objects.push_back(SnakeHead);
    for (auto &BodyPart : SnakeBody)
        objects.push_back(BodyPart);
    for (auto &Wall: Walls)
        objects.push_back(Wall);
    for (auto &Text : Texts)
        objects.push_back(Text);
    return objects;
}

/*std::vector<std::shared_ptr<Arcade::IObject>>*/
/*wprintf("press Rfor restart");
wprintf("press M for menu");            c 'est le gameover mais que en ncurses)
wprintf("press R for restart");*/



// int Arcade::Nibbler::CheckMovement()
// {
//    if (map[/*pos_nibbler*/] == NibblerWall || map[/*pos_nibbler*/] == Nibblertail)
//        return 84;
//    else if (map[/*pos_nibbler] == NibblerFruit) {
//        NibblerFruitGeneration()
//        /*add 1 size of NibblerTail*/
//    }
//    else {
//        /*Nibbler continue playing*/
//    }
// }



