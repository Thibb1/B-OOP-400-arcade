/*
** EPITECH PROJECT, 2022
** Pacman.cpp
** File description:
** TODO
*/

#include "Pacman.hpp"

extern "C" Arcade::Pacman *Arcade::entry_point()
{
    return new Arcade::Pacman;
}

Arcade::Pacman::Pacman() : position(7, 20), Direction(ARROW_LEFT), LastDirectionTry(ARROW_LEFT),
    Score(0), Height(0), Width(0), Lives(3), DirectionTries(0),
    Speed(500), Clock(NOW),
    RandomEngine(std::default_random_engine(RandomDevice()))
{
    std::fstream WallsFile("contents/Pacman.txt");
    std::string Line;
    while (std::getline(WallsFile, Line)) {
        if (!Width)
            Width = int (Line.length());
        for (int x = 0; x < int (Line.size()); x++) {
            switch (Line[x]) {
                case WALL:
                    Walls.push_back(std::make_shared<Tile>("contents/wall.png", ToString(1, WALL), BLUE, x, Height));
                    MapObjects.emplace(std::make_pair(x, Height), WALL);
                    break;
                case POINT:
                    if (x == int (position.first) && Height == int (position.second))
                        break;
                    Points.emplace(std::make_pair(x, Height), std::make_shared<Tile>("contents/point.png", ToString(1, POINT), BLUE, x, Height));
                    PointType.emplace(std::make_pair(x, Height), POINT);
                    break;
                default:
                    break;
            }
        }
        Height++;
    }
    SnakeHead = std::make_shared<Tile>("contents/pacpac.png", ToString(1, PACPAC), BLUE, position.first, position.second);
    SnakeHead->setRotation(180);
    GameOverText.push_back(std::make_shared<Text>("press R to restart", WHITE, 0 , Height + 1));
    GameOverText.push_back(std::make_shared<Text>("press M for menu", WHITE, 0 , Height + 2));
    ScoreText = std::make_shared<Text>("Score : " + std::to_string(Score), WHITE, 0, Height);
}

void Arcade::Pacman::ResetGame()
{
    Score = 0;
    position = {7, 20};
    Direction = ARROW_LEFT;
    LastDirectionTry = ARROW_LEFT;
    Lives = 3;
    Speed = 500;
    Clock = NOW;
    SnakeHead->setPosition(position);
    SnakeHead->setRotation(180);
    for (auto &PointPos: PointType)
        if (Points.find(PointPos.first) == Points.end())
            Points.emplace(PointPos.first, std::make_shared<Tile>("contents/point.png", ToString(1, POINT), BLUE, PointPos.first.first, PointPos.first.second));
    ScoreText->setText("Score : " + std::to_string(Score));
}

 std::vector<Arcade::Object> Arcade::Pacman::GameLoop(Input input)
{
    std::vector<Object> objects;
    SetDirection(input, false);
    MovePacman();
    PointPacman();

    for (auto &Wall: Walls)
        objects.push_back(Wall);
    for (auto &Point: Points)
        objects.push_back(Point.second);
    objects.push_back(SnakeHead);
    if (!true)
        for (auto &Text : GameOverText)
            objects.push_back(Text);
    objects.push_back(ScoreText);
    return objects;
}

float Arcade::Pacman::Modulo(float a, int b) {
    int mod = (b + (int (a) % b)) % b;
    if (int (a) != mod)
        return float (mod);
    return a;
}

void Arcade::Pacman::MovePacman() {
    auto Elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - Clock).count() * 15;
    if (Speed < Elapsed) {
        switch (Direction) {
            case ARROW_LEFT:
                if (WallInPosition(Position (position.first - .1, position.second)))
                    break;
                position.first -= .1;
                break;
            case ARROW_RIGHT:
                if (WallInPosition(Position (position.first + 1, position.second)))
                    break;
                position.first += .1;
                break;
            case ARROW_DOWN:
                if (WallInPosition(Position (position.first, position.second + 1)))
                    break;
                position.second += .1;
                break;
            case ARROW_UP:
                if (WallInPosition(Position (position.first, position.second - .1)))
                    break;
                position.second -= .1;
                break;
            default:
                break;
        }
        DirectionTries++;
        position.first = Modulo(position.first, Width);
        position.second = Modulo(position.second, Height);
        SnakeHead->setPosition(position);
        Clock = NOW;
        if (IsInt(position.first) && IsInt(position.second))
            SnakeHead->setCharacter("C");
        else
            SnakeHead->setCharacter("c");
    }

}


void Arcade::Pacman::SetDirection(Input input, bool retry) {
    switch (input) {
        case ARROW_LEFT:
            DirectionTries = retry ? DirectionTries : 0;
            LastDirectionTry = input;
            if (!IsInt(position.second) || WallInPosition(Position (position.first - .1, position.second)))
                break;
            Direction = input;
            SnakeHead->setRotation(180);
            break;
        case ARROW_RIGHT:
            DirectionTries = retry ? DirectionTries : 0;
            LastDirectionTry = input;
            if (!IsInt(position.second) || WallInPosition(Position (position.first + 1, position.second)))
                break;
            Direction = input;
            SnakeHead->setRotation(0);
            break;
        case ARROW_DOWN:
            DirectionTries = retry ? DirectionTries : 0;
            LastDirectionTry = input;
            if (!IsInt(position.first) || WallInPosition(Position (position.first, position.second + 1)))
                break;
            Direction = input;
            SnakeHead->setRotation(90);
            break;
        case ARROW_UP:
            DirectionTries = retry ? DirectionTries : 0;
            LastDirectionTry = input;
            if (!IsInt(position.first) || WallInPosition(Position (position.first, position.second - .1)))
                break;
            Direction = input;
            SnakeHead->setRotation(-90);
            break;
        default:
            if (DirectionTries < 10)
                SetDirection(LastDirectionTry, true);
            break;
    }
}


bool Arcade::Pacman::WallInPosition(Position NewPosition) {
    auto IntPos = PositionToIntPosition(NewPosition);
//    auto IntPos = NewPosition;
    if (MapObjects.find(IntPos) != MapObjects.end())
        if (MapObjects[IntPos] == WALL)
            return true;
    return false;
}

void Arcade::Pacman::PointPacman() {
    auto IntPos = PositionToIntPosition(position, true);
    if (Points.find(PositionToIntPosition(IntPos)) != Points.end()) {
        Points.erase(IntPos);
        Score += 10;
        ScoreText->setText("Score : " + std::to_string(Score));
    }
}

Arcade::Position Arcade::Pacman::PositionToIntPosition(Position oldPos, bool rounded) {
    if (rounded)
        return {int (round(oldPos.first)), int (round(oldPos.second))};
    return {int (oldPos.first), int (oldPos.second)};
}

bool Arcade::Pacman::IsInt(float a) {
    if (int (a) * 10 == int (a * 10))
        return true;
    return false;
}
