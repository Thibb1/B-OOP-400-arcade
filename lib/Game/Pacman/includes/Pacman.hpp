/*
** EPITECH PROJECT, 2022
** Nibbler.hpp
** File description:
** TODO
*/

#pragma once

#include "Game.hpp"

#include <random>
#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <thread>
#include <deque>
#include <random>


#include "ArcadeError.hpp"
#include "Display.hpp"

#define PACPAC 'C'
#define POINT '.'
#define WALL '#'
#define BONUS 'b'
#define GHOST 'G'
#define DOOR '-'
#define NOW std::chrono::high_resolution_clock::now()

namespace Arcade
{
    typedef std::chrono::high_resolution_clock::time_point Timer;
    typedef std::string ToString;
    typedef std::string Path;
    typedef std::chrono::milliseconds ms;

    typedef std::shared_ptr<Text> TextObject;
    typedef std::shared_ptr<Tile> TileObject;
    class Ghost {
    private:
        Position position;
        Position startPosition;
        TileObject GhostObject;
        Path startTexture;
        bool Alive;
        bool Scared;
    public:
        Ghost(const Path&, enum Color, Position);
        virtual ~Ghost() = default;
        TileObject getObject() {return GhostObject;}
        Position getPos() {return position;}
        void setPosition(Position);
        void reset();
        void resetTexture();
        void Kill();
        void Scare(long Since);
    };

    class Pacman : public IGame {
    private:
        Position position;
        Input Direction;
        Input LastDirectionTry;
        int DirectionTries;
        int Score;
        int Height;
        int Width;
        int Lives;
        int Level;
        bool Scatter;
        int ClockSpeed;
        Timer Clock;
        Timer BonusClock;
        std::vector<TextObject> GameOverText;
        TextObject ScoreText;
        TextObject LiveLevelText;
        std::vector<TileObject> Walls;
        std::vector<Ghost> Ghosts;
        std::map<Position, int> MapObjects;
        std::map<Position, TileObject> Points;
        std::map<Position, int> PointType;
        TileObject PacmanObject;
        std::random_device RandomDevice;
        std::default_random_engine RandomEngine;
    public:
        Pacman();
        ~Pacman() override = default;
        std::vector<Object> GameLoop(Input input) override;
        int GetScore() override {return Score;}
        void ResetGame() override;

        static float Modulo(float a, int b);

        void MovePacman();

        void SetDirection(Input input, bool retry);

        bool WallInPosition(Position, bool CheckDoor = true);

        void PointPacman();

        static Position PositionToIntPosition(Position, bool rounded = false);

        static bool IsInt(float a) ;

        void GhostPacman();

        void HitGhost();

        void LevelUp();

        void resetPoints();
    };
    extern "C" Pacman *entry_point();
}

