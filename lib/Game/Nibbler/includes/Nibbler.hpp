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

#define WALL '#'
#define NOW std::chrono::high_resolution_clock::now()

namespace Arcade
{
    typedef std::string ToString;
    typedef std::shared_ptr<Text> TextObject;
    typedef std::shared_ptr<Tile> TileObject;
    typedef std::shared_ptr<Sound> SoundObject;
    class Nibbler : public IGame {
    private:
        Position position;
        Input Direction;
        Input LastDirection;
        int Score;
        int Size;
        int Height;
        int Width;
        int Speed;
        std::chrono::high_resolution_clock::time_point Clock;
        std::vector<TextObject> GameOverText;
        TextObject ScoreText;
        std::vector<TileObject> Walls;
        std::map<Position, int> MapObjects;
        Position FruitPos;
        TileObject SnakeHead;
        TileObject Fruit;
        std::deque<TileObject> SnakeBody;
        bool CanMove;
        bool Eating;
        std::random_device RandomDevice;
        std::default_random_engine RandomEngine;
        std::vector<SoundObject> NibblerSounds;
    public:
        /**
         * Creating a new Nibbler object.
         */
        Nibbler();

        /**
         * The destructor for the Nibbler class
         */
        ~Nibbler() override = default;

        /**
         * Returning a vector of objects.
         */
        std::vector<Object> GameLoop(Input input) override;

        /**
         * Get the score of the game.
         *
         * @return The return type is an int, which is the score.
         */
        int GetScore() override {return Score;}

        /**
         * Reseting the game.
         */
        void ResetGame() override;

        /**
         * Adding a fruit to the map.
         */
        void AddFruit();

        /**
         * Moving the snake.
         */
        void MoveSnake(Input input);

        /**
         * Checking if the new position is a wall or not.
         */
        void CheckMovement(Position NewPosition);

        /**
         * Checking if the snake has collided with itself or the walls.
         */
        void GameOver();
    };
    extern "C" Nibbler *entry_point();
}

