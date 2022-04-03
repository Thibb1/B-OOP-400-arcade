/*
** EPITECH PROJECT, 2022
** Ghost.cpp
** File description:
** TODO
*/

#include "Ghost.hpp"

Arcade::Ghost::Ghost(const Path& path, int color, Position StartPosition, int stuckTime, bool normal) :
        position(StartPosition), startPosition(StartPosition), startTexture(path), Alive(true),
        Blocked(normal), InSpawn(normal), Normal(normal), Color(color),
        Direction(ARROW_UP), ClockSpeed(50), StuckTime(stuckTime), Clock(NOW), SpeedUp(NOW), StuckClock(NOW)
{
    std::random_device RandomDevice;
    RandomEngine = std::default_random_engine(RandomDevice());
    GhostObject = std::make_shared<Tile>(path, ToString(1, GHOST), Color, StartPosition.first, StartPosition.second);
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
    Clock = NOW;
    SpeedUp = NOW;
    StuckClock = NOW;
    ClockSpeed = 50;
    Blocked = Normal;
    InSpawn = Normal;
}

void Arcade::Ghost::resetTexture() {
    GhostObject->setTexture(startTexture);
    GhostObject->setColor(Color);
}

void Arcade::Ghost::Kill() {
    if (Alive) {
        Alive = false;
        Scared = false;
        GhostObject->setTexture("contents/Pacman/Eyes.png");
        GhostObject->setColor(196);
        ClockSpeed = 10;
    }
}

void Arcade::Ghost::Scare(long Since) {
    if (!Alive)
        return;
    if (Since < 10000) {
        Scared = true;
        if (Since > 8000 && Since % 350 < 150)
            resetTexture();
        else {
            GhostObject->setTexture("contents/Pacman/Scared.png");
            GhostObject->setColor(34);
        }
    } else if (Scared) {
        Scared = false;
        resetTexture();
    }
}

void Arcade::Ghost::Move(Pacman *pPacman) {
    auto Elapsed = std::chrono::duration_cast<ms>(NOW - Clock).count();
    if (Elapsed > ClockSpeed + (Scared && Alive) * ClockSpeed) {
        CheckInSpawn();
        Clock = NOW;
        auto x = position.first;
        auto y = position.second;
        Left = (Pacman::IsInt(y) && !pPacman->WallInPosition(Position (x - .1, y)));    // Left
        Right = (Pacman::IsInt(y) && !pPacman->WallInPosition(Position (x + 1, y)));     // Right
        Up = (Pacman::IsInt(x) && !pPacman->WallInPosition(Position (x, y - .1), !Alive || Blocked));    // Up
        Down = (Pacman::IsInt(x) && !pPacman->WallInPosition(Position (x, y + 1), Alive));     // Down

        switch (Direction) {
            case ARROW_LEFT:
                if (Left && Right)
                    Right = false;
                break;
            case ARROW_RIGHT:
                if (Left && Right)
                    Left = false;
                break;
            case ARROW_UP:
                if (Up && Down)
                    Down = false;
                break;
            case ARROW_DOWN:
                if (Up && Down)
                    Up = false;
            default:
                break;
        }
        if (Alive && !InSpawn && !Scared) {
            auto PacmanPos = pPacman->getPosition();
            PathTo(int (PacmanPos.first), int (PacmanPos.second));
        } else if (!Alive) {
            PathTo(11, 11);
        }
        while ((Left + Right + Up + Down) > 1) {
            int index = int (RandomEngine()) % 4;
            switch (index) {
                case 0:
                    Left = false;
                    break;
                case 1:
                    Right = false;
                    break;
                case 2:
                    Up = false;
                    break;
                case 3:
                    Down = false;
                    break;
                default:
                    break;
            }
        }
        MoveToTarget(pPacman);
        GhostObject->setPosition(position);
    }
    if (ClockSpeed > 25) {
        Elapsed = std::chrono::duration_cast<ms>(NOW - SpeedUp).count();
        if (Elapsed > 1000) {
            ClockSpeed--;
            SpeedUp = NOW;
        }
    }
    if (Blocked) {
        Elapsed = std::chrono::duration_cast<s>(NOW - StuckClock).count();
        if (Elapsed >= StuckTime)
            Blocked = false;
    }
}

void Arcade::Ghost::MoveToTarget(Pacman *pPacman) {
    if (Left) {
        position.first -= .1;
        Direction = ARROW_LEFT;
    } else if (Right) {
        position.first += .1;
        Direction = ARROW_RIGHT;
    } else if (Up) {
        position.second -= .1;
        Direction = ARROW_UP;
    } else if (Down) {
        position.second += .1;
        Direction = ARROW_DOWN;
    }
    position.first = Pacman::Modulo(position.first, pPacman->Width);
    position.second = Pacman::Modulo(position.second, pPacman->Height);
}

void Arcade::Ghost::CheckInSpawn() {
    auto Pos = Pacman::PositionToIntPosition(position, true);
    if (int (Pos.first) == 13 && int (position.second) == 12) {
        if (Alive) {
            InSpawn = false;
        } else {
            InSpawn = true;
            resetTexture();
            Alive = true;
            ClockSpeed = 50;
        }
    }
}

void Arcade::Ghost::PathTo(int xTarget, int yTarget) {
    auto x = int (round(position.first));
    auto y = int (round(position.second));
    if (Left && Right) {
        if (x > xTarget)
            Right = false;
        else
            Left = false;
    }
    if (Up && Down) {
        if (y > yTarget)
            Down = false;
        else
            Up = false;
    }
    if (x > xTarget) {
        if (y > yTarget) {
            if (Up && Right)
                Right = false;
            if (Down && Left)
                Down = false;
        } else {
            if (Up && Left)
                Up = false;
            if (Down && Right)
                Right = false;
        }
    } else {
        if (y > yTarget) {
            if (Up && Left)
                Left = false;
            if (Down && Right)
                Down = false;
        } else {
            if (Up && Right)
                Up = false;
            if (Down && Left)
                Left = false;
        }
    }
}
