#include <utility>

/*
** EPITECH PROJECT, 2022
** Object.hpp
** File description:
** TODO
*/

#pragma once

namespace Arcade
{
    enum Input {NOTHING, ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, N, P, F, B, M, R, ENTER, SPACE, EXIT};
    enum Color {BLUE, RED, WHITE, GREEN, PURPLE};

    class IObject {
    public:
        virtual ~IObject() = default;
    };
    typedef std::shared_ptr<IObject> Object;

    typedef std::pair<float, float> Position;
    typedef std::string TexturePath;
    class Tile : public IObject {
    private:
        TexturePath texturePath;
        Position position;
        Color color;
        std::string character;
        int rotation;
    public:
        Tile(TexturePath texturePath, std::string character, Color color= PURPLE, float positionX = 0, float positionY = 0) :
            texturePath(std::move(texturePath)),
            position(std::make_pair(positionX, positionY)),
            color(color),
            character(std::move(character)),
            rotation(0) {};
        ~Tile() override = default;
        TexturePath getTexturePath() {return texturePath;}
        Position getPosition() {return position;}
        [[nodiscard]] int getRotation() const {return rotation;}
        void setPosition(Position NewPosition) {position = NewPosition;}
        void setRotation(int NewRotation) {rotation = NewRotation;}
        void setCharacter(std::string NewText) {
            if (NewText != character)
                character = std::move(NewText);
        }
        [[nodiscard]] std::string getCharacter() {return character;}
    };

    class Text : public IObject {
    private:
        std::string text;
        Position position;
        Color color;
    public:
        explicit Text(std::string text, Color color = WHITE, float positionX = 0, float positionY = 0) :
                text(std::move(text)),
                position(std::make_pair(positionX, positionY)),
                color(color) {};
        ~Text() override = default;
        std::string getText() {return text;}
        Position getPosition() {return position;}
        void setText(std::string NewText) {
            if (NewText != text)
                text = std::move(NewText);
        }
    };
}