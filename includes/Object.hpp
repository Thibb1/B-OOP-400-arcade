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
        /**
         * The constructor for the Tile class
         *
         * @param texturePath The path to the texture file.
         * @param character The character that will be drawn on the tile.
         * @param color The color of the tile.
         * @param positionX The x-coordinate of the tile.
         * @param positionY The y-coordinate of the tile.
         */
        Tile(TexturePath texturePath, std::string character, int color = MAGENTA, float positionX = 0, float positionY = 0) :
            texturePath(std::move(texturePath)),
            position(std::make_pair(positionX, positionY)),
            color(color % 256),
            character(std::move(character)),
            rotation(0) {};

        /**
         * The destructor for the Tile class is empty
         */
        ~Tile() override = default;

        /**
         * Get the path to the texture file.
         *
         * @return The texture path.
         */
        TexturePath getTexturePath() {return texturePath;}

        /**
         * Return the current position
         *
         * @return The position of the current node.
         */
        Position getPosition() {return position;}

        /**
         * Get the rotation of the object.
         *
         * @return The rotation of the image.
         */
        [[nodiscard]] int getRotation() const {return rotation;}

        void setPosition(Position NewPosition) {position = NewPosition;}
        /**
         * Set the position of the object to the new position
         *
         * @param NewPosition The new position of the object.
         */

        /**
         * Set the rotation of the object to NewRotation.
         *
         * @param NewRotation The new rotation value.
         */
        void setRotation(int NewRotation) {rotation = NewRotation;}

        /**
         * The function sets the character variable to the value of the NewText
         * parameter
         *
         * @param NewText The new text to be set.
         */
        void setCharacter(std::string NewText) {
            if (NewText != character)
                character = std::move(NewText);
        }

        /**
         * The function takes a string and sets the texturePath variable to that
         * string
         *
         * @param NewTexture The path to the texture file.
         */
        void setTexture(std::string NewTexture) {
            if (NewTexture != texturePath)
                texturePath = std::move(NewTexture);
        }

        /**
         * Set the color to the given value
         *
         * @param Color The color of the text.
         */
        void setColor(int Color) {
            color = Color;
        }

        /**
         * Return the character that the player is currently playing as
         *
         * @return The character that was passed in.
         */
        [[nodiscard]] std::string getCharacter() {return character;}

        /**
         * Get the color of the object.
         *
         * @return The color of the node.
         */
        [[nodiscard]] int getColor() const {return color;}
    };

    class Text : public IObject {
    private:
        std::string text;
        Position position;
        int color;
    public:
        /**
         * Create a Text object with the given text, color, and position
         *
         * @param text The text to be displayed.
         * @param color The color of the text.
         * @param positionX The x-coordinate of the text.
         * @param positionY The y-coordinate of the text.
         */
        explicit Text(std::string text, int color = WHITE, float positionX = 0, float positionY = 0) :
                text(std::move(text)),
                position(std::make_pair(positionX, positionY)),
                color(color) {};

        /**
         * The destructor for the Text class
         */
        ~Text() override = default;

        /**
         * Return the text
         *
         * @return The text of the question.
         */
        std::string getText() {return text;}

        /**
         * Return the position of the player
         *
         * @return The position of the current node.
         */
        Position getPosition() {return position;}

        /**
         * Get the color of the object.
         *
         * @return The color of the node.
         */
        [[nodiscard]] int getColor() const {return color;}

        /**
         * If the text is different from the current text, then set the text to the
         * new text
         *
         * @param NewText The new text to set.
         */
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
        /**
         * Create a Sound object from a path to a music file
         *
         * @param path The path to the sound file.
         * @param loop If true, the sound will loop. If false, the sound will play
         * once.
         */
        explicit Sound(std::string path, bool loop = false) : Music(std::move(path)), Looping(loop) {};

        /**
         * This is the destructor
         */
        ~Sound() override = default;

        /**
         * Return the value of the Music member variable
         *
         * @return The value of the member variable Music.
         */
        [[nodiscard]] std::string getSound() const {return Music;};

        /**
         * Get the looping state of the sound.
         *
         * @return The value of Looping.
         */
        [[nodiscard]] bool getLoop() const {return Looping;}

        /**
         * Set the path of the music file to be played.
         *
         * @param path The path to the sound file.
         */
        void setSound(std::string path) {Music = std::move(path);};
    };
}