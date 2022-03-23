/*
** EPITECH PROJECT, 2022
** sdl2.hpp
** File description:
** TODO
*/

#pragma once

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Display.hpp"
#include "ArcadeError.hpp"

namespace Arcade
{
    class sdl2Texture {
    public:
        SDL_Texture *texture;
        SDL_Point center {};
        SDL_Rect rectangle {};
        sdl2Texture(const TexturePath&, SDL_Renderer *renderer);
        sdl2Texture(const std::string& Text, TTF_Font *font, SDL_Renderer *renderer);
        ~sdl2Texture();
        void SetPosition(Position position);
    };
    typedef std::string TextureName;
    typedef std::shared_ptr<sdl2Texture> Texture;
    class sdl2: public IDisplay {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        TTF_Font *font;
        std::map<TextureName, Texture> TextureMap;
    public:
        sdl2();
        ~sdl2() override;
        Input GetInput() override;
        void ClearScreen() override;
        void RefreshScreen() override;
        void DrawObject(Object object) override;
        void DrawTile(Tile *Tile);

        void DrawText(Text *pText);
    };
    extern "C" sdl2 *entry_point();
}