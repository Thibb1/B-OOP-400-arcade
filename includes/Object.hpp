/*
** EPITECH PROJECT, 2022
** Object.hpp
** File description:
** TODO
*/

#pragma once

#include <utility>

namespace Arcade
{
    enum Input {NOTHING, ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, N, P, F, B, M, R, ENTER, SPACE, EXIT};
    enum Color {
        BLUE,
        RED,
        GREEN,
        PINK,
        WHITE,
        CYAN,
        MAGENTA,
        YELLOW
    };

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
        int color;
        std::string character;
        int rotation;
    public:
        Tile(TexturePath texturePath, std::string character, int color = MAGENTA, float positionX = 0, float positionY = 0) :
            texturePath(std::move(texturePath)),
            position(std::make_pair(positionX, positionY)),
            color(color % 256),
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
        void setTexture(std::string NewTexture) {
            if (NewTexture != texturePath)
                texturePath = std::move(NewTexture);
        }
        void setColor(int Color) {
            color = Color;
        }
        [[nodiscard]] std::string getCharacter() {return character;}
        [[nodiscard]] int getColor() const {return color;}
    };

    class Text : public IObject {
    private:
        std::string text;
        Position position;
        int color;
    public:
        explicit Text(std::string text, int color = WHITE, float positionX = 0, float positionY = 0) :
                text(std::move(text)),
                position(std::make_pair(positionX, positionY)),
                color(color) {};
        ~Text() override = default;
        std::string getText() {return text;}
        Position getPosition() {return position;}
        [[nodiscard]] int getColor() const {return color;}
        void setText(std::string NewText) {
            if (NewText != text)
                text = std::move(NewText);
        }
    };
    class Sound : public IObject
    {
    private:
        std::string Music;
        bool Looping;
    public:
        explicit Sound(std::string path, bool loop = false) : Music(std::move(path)), Looping(loop) {};
        ~Sound() override = default;
        [[nodiscard]] std::string getSound() const {return Music;};
        [[nodiscard]] bool getLoop() const {return Looping;}
        void setSound(std::string path) {Music = std::move(path);};
    };
}