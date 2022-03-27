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

Arcade::Nibbler::Nibbler() : position(5, 5), Direction(ARROW_LEFT), LastDirection(Direction), Score(0), Size(3), Speed(500), Clock(NOW), CanMove(true)
{
    std::fstream WallsFile("contents/Nibbler.txt");
    std::string Line;
    int y = 0;
    if (!WallsFile.is_open())
        throw ArcadeMissingError("contents/Nibbler.txt");
    while (std::getline(WallsFile, Line)) {
        for (int x = 0; x < int (Line.size()); x++) {
            if (Line[x] == WALL) {
                Walls.push_back(std::make_shared<Tile>("contents/wall.png", WALL, BLUE, x, y));
                MapObjects[std::make_pair(x, y)] = WALL;
            }
        }
        y++;
    }
    SnakeHead = std::make_shared<Tile>("contents/SnakeHead.png", HEAD, BLUE, position.first, position.second);
    SnakeHead->setRotation(180);
    for (int x = 1; x <= Size; x++)
        SnakeBody.push_back(std::make_shared<Tile>("contents/SnakeBody.png", TAIL, BLUE,position.first + float (x),position.second));
    GameOverText.push_back(std::make_shared<Text>("press R to restart", WHITE, 0 , 0));
    GameOverText.push_back(std::make_shared<Text>("press M for menu", WHITE, 0 , 1));
}

void Arcade::Nibbler::ResetGame()
{
    Score = 0;
    position = {5, 5};
    Direction = ARROW_LEFT;
    LastDirection = Direction;
    Size = 4;
    Speed = 500;
    Clock = NOW;
    CanMove = true;
    SnakeHead->setPosition(position);
    SnakeHead->setRotation(180);
    SnakeBody.clear();
    for (int x = 1; x <= Size; x++)
        SnakeBody.push_back(std::make_shared<Tile>("contents/SnakeBody.png", TAIL, BLUE,position.first + float (x),position.second));
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
    MoveSnake(input);
    objects.push_back(SnakeHead);
    for (auto &BodyPart : SnakeBody)
        objects.push_back(BodyPart);
    for (auto &Wall: Walls)
        objects.push_back(Wall);
    if (!CanMove)
        for (auto &Text : GameOverText)
            objects.push_back(Text);
    return objects;
}

void Arcade::Nibbler::MoveSnake(Input input) {
    if (input != Direction) {
        switch (input) {
            case ARROW_LEFT:
                if (LastDirection == ARROW_RIGHT)
                    break;
                Direction = input;
                SnakeHead->setRotation(180);
                break;
            case ARROW_RIGHT:
                if (LastDirection == ARROW_LEFT)
                    break;
                Direction = input;
                SnakeHead->setRotation(0);
                break;
            case ARROW_DOWN:
                if (LastDirection == ARROW_UP)
                    break;
                Direction = input;
                SnakeHead->setRotation(90);
                break;
            case ARROW_UP:
                if (LastDirection == ARROW_DOWN)
                    break;
                Direction = input;
                SnakeHead->setRotation(-90);
                break;
            default:
                break;
        }
    }
    CheckMovement(position);
    auto Elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - Clock).count();
    if (Speed < Elapsed) {
        Clock = NOW;
        auto BackBodyPosition = position;
        switch (Direction) {
            case ARROW_LEFT:
                position.first -= 1;
                break;
            case ARROW_RIGHT:
                position.first += 1;
                break;
            case ARROW_DOWN:
                position.second += 1;
                break;
            case ARROW_UP:
                position.second -= 1;
                break;
            default:
                break;
        }
        CheckMovement(position);
        if (CanMove) {
            LastDirection = Direction;
            SnakeHead->setPosition(position);
            SnakeBody.pop_back();
            SnakeBody.push_front(std::make_shared<Tile>("contents/SnakeBody.png", TAIL, BLUE, BackBodyPosition.first, BackBodyPosition.second));
            Speed -= 1;
        }
    }
}

void Arcade::Nibbler::CheckMovement(Position NewPosition) {
    if (MapObjects.find(NewPosition) != MapObjects.end())
        CanMove = false;
}
