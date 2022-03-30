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
#define NOW std::chrono::high_resolution_clock::now()

namespace Arcade
{
    typedef std::string ToString;
    typedef std::shared_ptr<Text> TextObject;
    typedef std::shared_ptr<Tile> TileObject;
    class Pacman : public IGame {
    private:
        Position position;
        Input Direction;
        Input LastDirectionTry;
        int Score;
        int Height;
        int Width;
        int Lives;
        int DirectionTries;
        int Speed;
        std::chrono::high_resolution_clock::time_point Clock;
        std::vector<TextObject> GameOverText;
        TextObject ScoreText;
        std::vector<TileObject> Walls;
        std::map<Position, int> MapObjects;
        std::map<Position, TileObject> Points;
        std::map<Position, int> PointType;
        TileObject SnakeHead;
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

        bool WallInPosition(Position NewPosition);

        void PointPacman();

        static Position PositionToIntPosition(Position pair1, bool rounded = false);

        static bool IsInt(float a) ;
    };
    extern "C" Pacman *entry_point();
}

