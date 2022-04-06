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
#include "Ghost.hpp"

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
    typedef std::shared_ptr<Sound> SoundObject;
    class Ghost;

    class Pacman : public IGame {
    private:
        Position position;
        Input Direction;
        Input LastDirectionTry;
        int DirectionTries;
        int Score;
        int Lives;
        int Level;
        bool Scatter;
        int ClockSpeed;
        Timer Clock;
        Timer BonusClock;
        std::vector<TextObject> GameOverText;
        TextObject ScoreText;
        TextObject LiveLevelText;
        SoundObject SoundPacman;
        std::vector<SoundObject> PacmanSounds;
        bool Played{};
        bool Munch;
        std::vector<TileObject> Walls;
        std::vector<Arcade::Ghost> Ghosts;
        std::map<Position, int> MapObjects;
        std::map<Position, TileObject> Points;
        std::map<Position, int> PointType;
        TileObject PacmanObject;
    public:
        /**
         * Creating a new Pacman object.
         */
        Pacman();

        /**
         * The destructor is a special function that is called when an object is
         * destroyed
         */
        ~Pacman() override = default;

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
         * A function that returns the modulo of a and b.
         */
        static float Modulo(float a, int b);

        /**
         * Moving the Pacman object to the next position.
         */
        void MovePacman();

        /**
         * Setting the direction of the Pacman object.
         */
        void SetDirection(Input input, bool retry);

        /**
         * Checking if there is a wall in the position of the Pacman.
         */
        bool WallInPosition(Position, bool CheckDoor = true);

        /**
         * Checking if the Pacman is on a point.
         */
        void PointPacman();

        /**
         * Converting a Position object to an int.
         */
        static Position PositionToIntPosition(Position, bool rounded = false);

        /**
         * Checking if the float is an integer.
         */
        static bool IsInt(float a) ;

        /**
         * Checking if the Pacman is on a ghost.
         */
        void GhostPacman();

        /**
         * Checking if the Pacman is on a ghost.
         */
        void HitGhost();

        /**
* Increasing the level of the game. */
        void LevelUp();

        /**
* Reseting the points of the game. */
        void resetPoints();

        int Width;
        int Height;

        /**
         * Updating the score of the game.
         */
        void UpdateScores();

        /**
         * Return the position of the player
         *
         * @return The position of the current node.
         */
        Position getPosition() {return position;}
    };
    extern "C" Pacman *entry_point();
}

