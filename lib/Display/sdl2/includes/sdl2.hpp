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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "ArcadeError.hpp"

namespace Arcade
{
    class sdl2Texture {
    public:
        SDL_Texture *texture;
        SDL_Point center {};
        SDL_Rect rectangle {};
        sdl2Texture(const TexturePath&, SDL_Renderer *renderer);
        sdl2Texture(const TexturePath& Text, TTF_Font *font, SDL_Renderer *renderer);
        ~sdl2Texture();
        void SetPosition(Position position);
    };
    typedef std::string SoundPath;
    class sdl2Sound {
    public:
        Mix_Music *music{};
        bool Looping;
        explicit sdl2Sound(const SoundPath&, bool loop = false);
        ~sdl2Sound() {
            Mix_FreeMusic(music);
        }
        void play() const {
            Mix_PlayMusic(music, Looping ? 9999 : 1);
        }
    };
    typedef std::shared_ptr<sdl2Texture> Texture;
    typedef std::shared_ptr<sdl2Sound> Music;
    class sdl2: public IDisplay {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        TTF_Font *font;
        std::map<TexturePath, Texture> TextureMap;
        std::unordered_map<SoundPath, Music> SoundMap;
    public:
        sdl2();
        ~sdl2() override;
        Input GetInput() override;
        void ClearScreen() override;
        void RefreshScreen() override;
        void DrawObject(Object object) override;
        void DrawTile(Tile *Tile);

        void DrawText(Text *pText);

        void PlaySound(Sound *pSound);
    };
    extern "C" sdl2 *entry_point();
}