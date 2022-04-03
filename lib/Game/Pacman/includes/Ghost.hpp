/*
** EPITECH PROJECT, 2022
** Ghost.hpp
** File description:
** TODO
*/

#pragma once

#include "Pacman.hpp"

namespace Arcade {
    typedef std::string Path;
    typedef std::chrono::high_resolution_clock::time_point Timer;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::seconds s;
    typedef std::shared_ptr<Text> TextObject;
    typedef std::shared_ptr<Tile> TileObject;
    class Pacman;
    class Ghost {
    private:
        Position position;
        Position startPosition;
        TileObject GhostObject;
        Path startTexture;
        bool Alive;
        bool Scared{};
        bool Blocked;
        bool InSpawn;
        bool Normal;
        int Color;
        bool Left{};
        bool Right{};
        bool Up{};
        bool Down{};
        Input Direction;
        int ClockSpeed;
        int StuckTime;
        Timer Clock;
        Timer SpeedUp;
        Timer StuckClock;
        std::default_random_engine RandomEngine;
    public:
        Ghost(const Path&, int Color, Position, int stuckTime = 10, bool normal = true);
        virtual ~Ghost() = default;
        TileObject getObject() {return GhostObject;}
        Position getPos() {return position;}
        void setPosition(Position);
        void reset();
        void resetTexture();
        void Kill();
        void Move(Arcade::Pacman *pPacman);
        void Scare(long Since);

        void MoveToTarget(Pacman *pPacman);
        [[nodiscard]] bool isAlive() const {return Alive;}

        void CheckInSpawn();

        void PathTo(int xTarget, int yTarget);
    };
}
