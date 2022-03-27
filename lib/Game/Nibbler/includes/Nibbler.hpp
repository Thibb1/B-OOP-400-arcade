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


#include "ArcadeError.hpp"
#include "Display.hpp"

#define FRUIT '*'
#define WALL '#'
#define TAIL 's'
#define HEAD 'S'
#define NOW std::chrono::high_resolution_clock::now()

namespace Arcade
{
    typedef std::shared_ptr<Text> TextObject;
    typedef std::shared_ptr<Tile> TileObject;
    class Nibbler : public IGame {
    private:
        Position position;
        Input Direction;
        Input LastDirection;
        int Score;
        int Size;
        int Speed;
        std::chrono::high_resolution_clock::time_point Clock;
        std::vector<TextObject> GameOverText;
        std::vector<TileObject> Walls;
        std::map<Position, int> MapObjects;
        TileObject SnakeHead;
        std::deque<TileObject> SnakeBody;
        bool CanMove;
    public:
        Nibbler();
        ~Nibbler() override = default;
        std::vector<Object> GameLoop(Input input) override;
        int GetScore() override {return Score;}
        void ResetGame() override;
        void NibblerFruitGeneration();
        void MoveSnake(Input input);
        void CheckMovement(Position NewPosition);
    };
    extern "C" Nibbler *entry_point();
}

