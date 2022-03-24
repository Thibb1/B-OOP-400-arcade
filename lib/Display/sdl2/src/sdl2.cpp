/*
** EPITECH PROJECT, 2022
** sdl2.cpp
** File description:
** TODO
*/

#include "sdl2.hpp"

extern "C" Arcade::sdl2 *Arcade::entry_point()
{
    return new Arcade::sdl2;
}

Arcade::sdl2::sdl2() : window(nullptr), renderer(nullptr), font(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        throw ArcadeRuntimeError();
    window = SDL_CreateWindow("Arcade - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
        throw ArcadeRuntimeError();
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw ArcadeRuntimeError();
    if (TTF_Init() == -1)
        throw ArcadeRuntimeError();
    font = TTF_OpenFont("contents/FiraCode-Regular.ttf", 20);
    if (!font)
        throw ArcadeRuntimeError();
}

Arcade::sdl2::~sdl2()
{
    TextureMap.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

Arcade::Input Arcade::sdl2::GetInput() {
    SDL_Event Event;
    Input input = NOTHING;
    while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_QUIT)
            input = EXIT;
        else if (Event.type == SDL_KEYDOWN) {
            switch (Event.key.keysym.sym) {
                case SDLK_LEFT:
                    input = ARROW_LEFT;
                    break;
                case SDLK_RIGHT:
                    input = ARROW_RIGHT;
                    break;
                case SDLK_UP:
                    input = ARROW_UP;
                    break;
                case SDLK_DOWN:
                    input = ARROW_DOWN;
                    break;
                case SDLK_n:
                    input = N;
                    break;
                case SDLK_p:
                    input = P;
                    break;
                case SDLK_f:
                    input = F;
                    break;
                case SDLK_b:
                    input = B;
                    break;
                case SDLK_m:
                    input = M;
                    break;
                case SDLK_r:
                    input = R;
                    break;
                case SDLK_RETURN:
                    input = ENTER;
                    break;
                case SDLK_ESCAPE:
                    input = EXIT;
                    break;
                default:
                    break;
            }
        }
    }
    return input;
}

void Arcade::sdl2::ClearScreen()
{
    SDL_RenderClear(renderer);
}

void Arcade::sdl2::RefreshScreen()
{
    SDL_RenderPresent(renderer);
}

void Arcade::sdl2::DrawObject(Arcade::Object object)
{
    auto Tile = dynamic_cast<Arcade::Tile *>(object.get());
    if (Tile)
        DrawTile(Tile);
    auto Text = dynamic_cast<Arcade::Text *>(object.get());
    if (Text)
        DrawText(Text);
}

void Arcade::sdl2::DrawTile(Arcade::Tile *Tile)
{
    TexturePath path = Tile->getTexturePath();
    if (TextureMap.find(path) == TextureMap.end())
        TextureMap[path] = std::make_shared<sdl2Texture>(path, renderer);
    Texture texture = TextureMap[path];
    texture->SetPosition(Tile->getPosition());
    SDL_RenderCopyEx(renderer, texture->texture, nullptr, &texture->rectangle, Tile->getRotation(), &texture->center, static_cast<SDL_RendererFlip>(SDL_FLIP_NONE));
}

void Arcade::sdl2::DrawText(Arcade::Text *Text)
{
    auto TextTexture = std::make_shared<sdl2Texture>(Text->getText(), font, renderer);
    TextTexture->SetPosition(Text->getPosition());
    SDL_RenderCopy(renderer, TextTexture->texture, nullptr, &TextTexture->rectangle);
}


Arcade::sdl2Texture::sdl2Texture(const Arcade::TexturePath& path, SDL_Renderer *renderer) : texture(IMG_LoadTexture(renderer, path.c_str()))
{
    if (!texture)
        throw ArcadeRuntimeError();
    SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
    center.x = rectangle.w / 2;
    center.y = rectangle.h / 2;
}

Arcade::sdl2Texture::sdl2Texture(const std::string& Text, TTF_Font *font, SDL_Renderer *renderer) : texture(nullptr)
{
    auto  TextSurface = TTF_RenderText_Solid(font, Text.c_str(), SDL_Color {225, 225, 225, 255});
    if (!TextSurface)
        throw ArcadeRuntimeError();
    texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    if (!texture)
        throw ArcadeRuntimeError();
    SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
    SDL_FreeSurface(TextSurface);
}

Arcade::sdl2Texture::~sdl2Texture()
{
    SDL_DestroyTexture(texture);
}

void Arcade::sdl2Texture::SetPosition(Position position)
{
    rectangle.x = int (position.first * 30);
    rectangle.y = int (position.second * 30);
}
