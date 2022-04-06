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
        /**
         * Creating a Ghost object.
         */
        Ghost(const Path&, int Color, Position, int stuckTime = 10, bool normal = true);

        /**
         * The destructor is a special function that is called when an object is
         * destroyed
         */
        virtual ~Ghost() = default;

        /**
         * Returns the object that the ghost is currently occupying
         *
         * @return The object that is being returned is the GhostObject.
         */
        TileObject getObject() {return GhostObject;}

        /**
         * Return the position of the player
         *
         * @return The position of the current node.
         */
        Position getPos() {return position;}

        /**
         * Setting the position of the ghost to the position that is passed in.
         */
        void setPosition(Position);

        /**
         * Resetting the ghost to its original position.
         */
        void reset();

        /**
         * Resetting the texture of the ghost to the original texture.
         */
        void resetTexture();

        /**
         * This is a function that is called when the ghost is killed.
         */
        void Kill();

        /**
         * This is a function that is called when the ghost is moving.
         */
        void Move(Arcade::Pacman *pPacman);

        /**
         * This is a function that is called when the ghost is scared.
         */
        void Scare(long Since);

        /**
         * Moving the ghost to the target position.
         */
        void MoveToTarget(Pacman *pPacman);

        /**
         * If the object is alive, return true, otherwise return false
         *
         * @return The return type is bool, which is a type that can only be true
         * or false.
         */
        [[nodiscard]] bool isAlive() const {return Alive;}

        /**
         * Checking if the ghost is in the spawn area.
         */
        void CheckInSpawn();

        /**
         * This is a function that is called when the ghost is trying to get to a target position.
         */
        void PathTo(int xTarget, int yTarget);
    };
}
