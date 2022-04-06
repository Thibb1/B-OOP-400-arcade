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
        /**
         * This is a constructor.
         * @param texture is the texture to set.
         * @param renderer is the renderer to set.
         */
        sdl2Texture(const TexturePath& texture, SDL_Renderer *renderer);

        /**
         * This is a constructor.
         * @param Text is the texture to set.
         * @param font is the font to set.
         * @param renderer is the renderer to set.
         */
        sdl2Texture(const TexturePath& Text, TTF_Font *font, SDL_Renderer *renderer);

        /**
         * This is a destructor.
         */
        ~sdl2Texture();

        /**
         * This function is used to set the position of the texture.
         * @param position is the position to set.
         */
        void SetPosition(Position position);
    };
    typedef std::string SoundPath;
    class sdl2Sound {
    public:
        Mix_Music *music{};
        bool Looping;

        /**
         * This is a constructor.
         * @param SoundPath is the path to the sound file.
         * @param bool is the looping to set.
         */
        explicit sdl2Sound(const SoundPath&, bool loop = false);

        /**
         * This is a destructor.
         */
        ~sdl2Sound() {
            Mix_FreeMusic(music);
        }

        /**
         * This function is used to play the sound.
         */
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
        /**
         * sdl2 constructor
         */
        sdl2();

        /**
         * sdl2 destructor
         */
        ~sdl2() override;

        /** Returning the input of the user.
         * @return the input of the user.
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
         * @param Object is the object to draw.
         */
        void DrawObject(Object object) override;

        /**
         * Drawing the tile on the screen.
         * @param Tile is the tile to draw.
         */
        void DrawTile(Tile *Tile);

        /**
         * Drawing text on the screen.
         * @param Text is the text to draw.
         */
        void DrawText(Text *pText);

        /**
         * Playing the sound.
         * @param Sound is the sound to play.
         */
        void PlaySound(Sound *pSound);
    };
    extern "C" sdl2 *entry_point();
}