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

#include "ArcadeError.hpp"
#include "Display.hpp"

#define FRUIT '*'
#define WALL '#'
#define TAIL 's'
#define HEAD 'S'

namespace Arcade
{
    typedef std::shared_ptr<Text> TextObject;
    typedef std::shared_ptr<Tile> TileObject;
    class Nibbler : public IGame {
    private:
        Position position;
        Input Direction;
        int Score;
        int Size;
        std::vector<TextObject> Texts;
        std::vector<TileObject> Walls;
        TileObject SnakeHead;
        std::vector<TileObject> SnakeBody;
    public:
        Nibbler();
        ~Nibbler() override = default;
        std::vector<Object> GameLoop(Input input) override;
        int GetScore() override {return Score;}
        void ResetGame() override;
        void NibblerFruitGeneration();

        void MoveSnake(Input input);
    };
    extern "C" Nibbler *entry_point();
}

