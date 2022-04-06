
/*
** EPITECH PROJECT, 2022
** sdl2.hpp
** File description:
** TODO
*/

#pragma once

#include "Display.hpp"

#include <map>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "ArcadeError.hpp"

namespace Arcade
{
    typedef std::string SoundPath;
    class sfml: public IDisplay {
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Font font;
        std::map<TexturePath, std::shared_ptr<sf::Texture>> TextureMap{};
        std::unordered_map<SoundPath, std::pair<std::shared_ptr<sf::SoundBuffer>, std::shared_ptr<sf::Sound>>> SoundMap;
    public:
        /**
         * Creating a new instance of the sfml class.
         */
        sfml();

        /**
         * This is a destructor. It is called when the object is destroyed.
         */
        ~sfml() override;

        /**
         * Returning the input of the user.
         */
        Input GetInput() override;

        /**
         * Clearing the screen.
         */
        void ClearScreen() override;

        /**
         * Refreshing the screen.
         */
        void RefreshScreen() override;

        /**
         * Drawing the object on the screen.
         */
        void DrawObject(Object object) override;

        /**
         * Drawing a tile.
         */
        void DrawTile(Tile *tile);

        /**
         * Drawing text on the screen.
         */
        void DrawText(Text *text);

        /**
         * Playing a sound.
         */
        void PlaySound(Sound *sound);
    };
    extern "C" sfml *entry_point();
}