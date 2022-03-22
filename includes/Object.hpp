/*
** EPITECH PROJECT, 2022
** Object.hpp
** File description:
** TODO
*/

#pragma once

namespace Arcade
{
    enum Input {NOTHING, ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, N, P, F, B, M, R, ENTER, EXIT};
    enum Color {BLUE, RED, WHITE, GREEN, PURPLE};

    typedef std::pair<float, float> Position;
    typedef std::string TexturePath;
    class IObject {
    public:
        virtual ~IObject() = default;
    };
    class Tile : public IObject {
    private:
        TexturePath texturePath;
        Position position;
        Color color;
        int character;
        int rotation;
    public:
        Tile(TexturePath texturePath, int character, Color color= PURPLE, float positionX = 0, float positionY = 0) :
            texturePath(std::move(texturePath)),
            position(std::make_pair(positionX, positionY)),
            color(color),
            character(character),
            rotation(0) {};
        ~Tile() override = default;
        TexturePath getTexturePath() {return texturePath;}
        Position getPosition() {return position;}
        int getRotation() {return rotation;}
    };
    typedef std::shared_ptr<IObject> Object;
}