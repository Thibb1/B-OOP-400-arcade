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

Arcade::Pacman::Pacman() : position(7, 20), Direction(NOTHING), LastDirectionTry(ARROW_UP), DirectionTries(0),
                           Score(0), Height(0), Width(0), Lives(3), Level(0), Scatter(false),
                           ClockSpeed(30), Clock(NOW), BonusClock(NOW),
                           RandomEngine(std::default_random_engine(RandomDevice()))
{
    std::fstream WallsFile("contents/Pacman/Pacman.txt");
    std::string Line;
    while (std::getline(WallsFile, Line)) {
        if (!Width)
            Width = int (Line.length());
        for (int x = 0; x < int (Line.size()); x++) {
            switch (Line[x]) {
                case WALL:
                    Walls.push_back(std::make_shared<Tile>("contents/Pacman/Wall.png", ToString(1, WALL), BLUE, x, Height));
                    MapObjects.emplace(std::make_pair(x, Height), WALL);
                    break;
                case DOOR:
                    Walls.push_back(std::make_shared<Tile>("contents/Pacman/Door.png", ToString(1, DOOR), YELLOW, x, Height));
                    MapObjects.emplace(std::make_pair(x, Height), DOOR);
                    break;
                case POINT:
                    if (x == int (position.first) && Height == int (position.second))
                        break;
                    Points.emplace(std::make_pair(x, Height), std::make_shared<Tile>("contents/Pacman/Point.png", ToString(1, POINT), BLUE, x, Height));
                    PointType.emplace(std::make_pair(x, Height), POINT);
                    break;
                case BONUS:
                    Points.emplace(std::make_pair(x, Height), std::make_shared<Tile>("contents/Pacman/Bonus.png", ToString(1, BONUS), BLUE, x, Height));
                    PointType.emplace(std::make_pair(x, Height), BONUS);
                default:
                    break;
            }
        }
        Height++;
    }
    WallsFile.close();
    Ghosts.push_back(Ghost("contents/Pacman/Blinky.png", RED, {13, 11}));
    Ghosts.push_back(Ghost("contents/Pacman/Pinky.png", PINK, {11, 14}));
    Ghosts.push_back(Ghost("contents/Pacman/Inky.png", CYAN, {12, 14}));
    Ghosts.push_back(Ghost("contents/Pacman/Clyde.png", YELLOW, {15, 14}));
    PacmanObject = std::make_shared<Tile>("contents/Pacman/Pacman.png", ToString(1, PACPAC), BLUE, position.first, position.second);
    PacmanObject->setRotation(180);
    GameOverText.push_back(std::make_shared<Text>("press R to restart", WHITE, 18, Height + 1));
    GameOverText.push_back(std::make_shared<Text>("press M for menu", WHITE, 0 , Height + 1));
    ScoreText = std::make_shared<Text>("Score : " + std::to_string(Score), WHITE, 20, Height);
    LiveLevelText = std::make_shared<Text>("Lives : " + std::to_string(Lives) + " Level : " + std::to_string(Level), WHITE, 0, Height);
}

void Arcade::Pacman::ResetGame()
{
    Score = 0;
    position = {7, 20};
    Direction = NOTHING;
    LastDirectionTry = ARROW_UP;
    Lives = 3;
    Level = 0;
    Scatter = false;
    ClockSpeed = 30;
    Clock = NOW;
    PacmanObject->setPosition(position);
    PacmanObject->setRotation(180);
    for (auto &item: Ghosts)
        item.reset();
    resetPoints();
    ScoreText->setText("Score : " + std::to_string(Score));
    LiveLevelText->setText("Lives : " + std::to_string(Lives) + " Level : " + std::to_string(Level));
}

 std::vector<Arcade::Object> Arcade::Pacman::GameLoop(Input input)
{
    std::vector<Object> objects;
    SetDirection(input, false);
    MovePacman();
    PointPacman();
    GhostPacman();
    if (Points.empty())
        LevelUp();
    for (auto &Wall: Walls)
        objects.push_back(Wall);
    for (auto &Point: Points)
        objects.push_back(Point.second);
    for (auto &item: Ghosts)
        objects.push_back(item.getObject());
    objects.push_back(PacmanObject);
    if (!Lives)
        for (auto &Text : GameOverText)
            objects.push_back(Text);
    objects.push_back(ScoreText);
    objects.push_back(LiveLevelText);
    return objects;
}

float Arcade::Pacman::Modulo(float a, int b) {
    int mod = (b + (int (a) % b)) % b;
    if (int (a) != mod)
        return float (mod);
    return a;
}

void Arcade::Pacman::MovePacman() {
    auto Elapsed = std::chrono::duration_cast<ms>(NOW - Clock).count();
    if (Lives && ClockSpeed < Elapsed) {
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
        PacmanObject->setPosition(position);
        Clock = NOW;
        if (IsInt(position.first) && IsInt(position.second))
            PacmanObject->setCharacter("C");
        else
            PacmanObject->setCharacter("c");
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
            PacmanObject->setRotation(180);
            break;
        case ARROW_RIGHT:
            DirectionTries = retry ? DirectionTries : 0;
            LastDirectionTry = input;
            if (!IsInt(position.second) || WallInPosition(Position (position.first + 1, position.second)))
                break;
            Direction = input;
            PacmanObject->setRotation(0);
            break;
        case ARROW_DOWN:
            DirectionTries = retry ? DirectionTries : 0;
            LastDirectionTry = input;
            if (!IsInt(position.first) || WallInPosition(Position (position.first, position.second + 1)))
                break;
            Direction = input;
            PacmanObject->setRotation(90);
            break;
        case ARROW_UP:
            DirectionTries = retry ? DirectionTries : 0;
            LastDirectionTry = input;
            if (!IsInt(position.first) || WallInPosition(Position (position.first, position.second - .1)))
                break;
            Direction = input;
            PacmanObject->setRotation(-90);
            break;
        default:
            if (DirectionTries < 10)
                SetDirection(LastDirectionTry, true);
            break;
    }
}


bool Arcade::Pacman::WallInPosition(Position NewPosition, bool CheckDoor) {
    auto IntPos = PositionToIntPosition(NewPosition);
    if (MapObjects.find(IntPos) != MapObjects.end())
        if (MapObjects[IntPos] == WALL || (CheckDoor && MapObjects[IntPos] == DOOR))
            return true;
    return false;
}

void Arcade::Pacman::PointPacman() {
    auto IntPos = PositionToIntPosition(position, true);
    if (Points.find(PositionToIntPosition(IntPos)) != Points.end()) {
        switch (PointType[IntPos]) {
            case POINT:
                Points.erase(IntPos);
                Score += 10;
                break;
            case BONUS:
                Points.erase(IntPos);
                Score += 50;
                BonusClock = NOW;
                Scatter = true;
                break;
            default:
                break;
        }
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

void Arcade::Pacman::GhostPacman() {
    auto Elapsed = std::chrono::duration_cast<ms>(NOW - BonusClock).count();
    auto IntPosPacman = PositionToIntPosition(position, true);
    if (Elapsed >= 10000 && Scatter) {
        for (auto &item: Ghosts)
            item.Scare(Elapsed);
        Scatter = false;
    }
    for (auto &item: Ghosts) {
        auto IntPosGhost = PositionToIntPosition(item.getPos(), true);
        if (Scatter)
            item.Scare(Elapsed);
        if (IntPosGhost == IntPosPacman) {
            if (!Scatter) {
                HitGhost();
            } else {
                item.Kill();
            }
        }
    }
}

void Arcade::Pacman::HitGhost() {
    if (Lives) {
        Lives--;
        LiveLevelText->setText("Lives : " + std::to_string(Lives) + " Level : " + std::to_string(Level));
    }
    if (Lives) {
        for (auto &item: Ghosts)
            item.reset();
        ClockSpeed = 30;
        position = {7, 20};
        Direction = NOTHING;
        LastDirectionTry = ARROW_UP;
        PacmanObject->setRotation(180);
        PacmanObject->setPosition(position);
    }
}

void Arcade::Pacman::LevelUp() {
    resetPoints();
    Level++;
    position = {7, 20};
    Direction = NOTHING;
    LastDirectionTry = ARROW_UP;
    PacmanObject->setRotation(180);
    PacmanObject->setPosition(position);
    if (ClockSpeed > 10)
        ClockSpeed -= 2;
    LiveLevelText->setText("Lives : " + std::to_string(Lives) + " Level : " + std::to_string(Level));
}

void Arcade::Pacman::resetPoints() {
    for (auto &Point: PointType)
        if (Points.find(Point.first) == Points.end()) {
            if (Point.second == POINT)
                Points.emplace(Point.first, std::make_shared<Tile>("contents/Pacman/Point.png", ToString(1, POINT), BLUE, Point.first.first, Point.first.second));
            else
                Points.emplace(Point.first, std::make_shared<Tile>("contents/Pacman/Bonus.png", ToString(1, BONUS), BLUE, Point.first.first, Point.first.second));
        }
}

Arcade::Ghost::Ghost(const Path& path, enum Color color, Position StartPosition) : position(StartPosition), startPosition(StartPosition),
        startTexture(path), Alive(true)
{
    GhostObject = std::make_shared<Tile>(path, ToString(1, GHOST), color, StartPosition.first, StartPosition.second);
}

void Arcade::Ghost::setPosition(Position NewPosition) {
    position = NewPosition;
    GhostObject->setPosition(NewPosition);
}

void Arcade::Ghost::reset() {
    resetTexture();
    setPosition(startPosition);
    Alive = true;
    Scared = false;
}

void Arcade::Ghost::resetTexture() {
    GhostObject->setTexture(startTexture);
}

void Arcade::Ghost::Kill() {
    Alive = false;
    Scared = false;
    GhostObject->setTexture("contents/Pacman/Eyes.png");
}

void Arcade::Ghost::Scare(long Since) {
    if (!Alive)
        return;
    if (Since < 10000) {
        Scared = true;
        if (Since > 8000 && Since % 350 < 150)
            resetTexture();
        else
            GhostObject->setTexture("contents/Pacman/Scared.png");
    } else if (Scared) {
        Scared = false;
        resetTexture();
    }
}