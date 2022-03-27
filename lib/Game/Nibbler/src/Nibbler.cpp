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

Arcade::Nibbler::Nibbler() : position(5, 5), Direction(ARROW_LEFT), LastDirection(Direction),
    Score(0), Size(3), Height(0), Width(0),
    Speed(500), Clock(NOW), CanMove(true), Eating(false),
    RandomEngine(std::default_random_engine(RandomDevice()))
{
    std::fstream WallsFile("contents/Nibbler.txt");
    std::string Line;
    if (!WallsFile.is_open())
        throw ArcadeMissingError("contents/Nibbler.txt");
    while (std::getline(WallsFile, Line)) {
        if (!Width)
            Width = int (Line.length());
        for (int x = 0; x < int (Line.size()); x++) {
            if (Line[x] == WALL) {
                Walls.push_back(std::make_shared<Tile>("contents/wall.png", WALL, BLUE, x, Height));
                MapObjects.emplace(std::make_pair(x, Height), WALL);
            }
        }
        Height++;
    }
    SnakeHead = std::make_shared<Tile>("contents/SnakeHead.png", HEAD, BLUE, position.first, position.second);
    SnakeHead->setRotation(180);
    Fruit = std::make_shared<Tile>("contents/SnakeHead.png", FRUIT, BLUE, 1, 1);
    for (int x = 1; x <= Size; x++)
        SnakeBody.push_back(std::make_shared<Tile>("contents/SnakeBody.png", TAIL, BLUE,position.first + float (x),position.second));
    GameOverText.push_back(std::make_shared<Text>("press R to restart", WHITE, 0 , Height));
    GameOverText.push_back(std::make_shared<Text>("press M for menu", WHITE, 0 , Height + 1));
    AddFruit();
}

void Arcade::Nibbler::ResetGame()
{
    Score = 0;
    position = {5, 5};
    Direction = ARROW_LEFT;
    LastDirection = Direction;
    Size = 3;
    Speed = 500;
    Clock = NOW;
    CanMove = true;
    Eating = false;
    SnakeHead->setPosition(position);
    SnakeHead->setRotation(180);
    SnakeBody.clear();
    for (int x = 1; x <= Size; x++)
        SnakeBody.push_back(std::make_shared<Tile>("contents/SnakeBody.png", TAIL, BLUE,position.first + float (x),position.second));
    AddFruit();
}

void Arcade::Nibbler::AddFruit()
{
    while (true) {
        bool InBodyPart = false;
        FruitPos.second = float (int (RandomEngine()) % (Height - 1) + 1);
        FruitPos.first = float (int (RandomEngine()) % (Width - 1) + 1);
        if (MapObjects.find(FruitPos) != MapObjects.end())
            continue;
        if (FruitPos == position)
            continue;
        for (auto &BodyPart : SnakeBody)
            if (FruitPos == BodyPart->getPosition()) {
                InBodyPart = true;
                break;
            }
        if (InBodyPart)
            continue;
        break;
    }
    Fruit->setPosition(FruitPos);
}

 std::vector<Arcade::Object> Arcade::Nibbler::GameLoop(Input input)
{
    std::vector<Object> objects;
    MoveSnake(input);
    objects.push_back(Fruit);
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
            SnakeBody.push_front(std::make_shared<Tile>("contents/SnakeBody.png", TAIL, BLUE, BackBodyPosition.first, BackBodyPosition.second));
            if (!Eating)
                SnakeBody.pop_back();
            else
                AddFruit();
            Eating = false;
            if (Speed > 140)
                Speed -= 1;
        }
    }
}

void Arcade::Nibbler::CheckMovement(Position NewPosition) {
    if (MapObjects.find(NewPosition) != MapObjects.end())
        if (MapObjects[NewPosition] == WALL)
            CanMove = false;
    if (NewPosition == FruitPos)
        Eating = true;
    for (auto &BodyPart : SnakeBody)
        if (NewPosition == BodyPart->getPosition())
            CanMove = false;
}
