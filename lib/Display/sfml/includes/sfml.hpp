
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

#include "ArcadeError.hpp"

namespace Arcade
{
    class sfml: public IDisplay {
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Font font;
        std::map<TexturePath, std::shared_ptr<sf::Texture>> TextureMap{};
    public:
        sfml();
        ~sfml() override;
        Input GetInput() override;
        void ClearScreen() override;
        void RefreshScreen() override;
        void DrawObject(Object object) override;
        void DrawTile(Tile *tile);
        void DrawText(Text *text);
        void PlaySound(Sound *sound);
    };
    extern "C" sfml *entry_point();
}