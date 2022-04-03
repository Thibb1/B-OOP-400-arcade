/*
** EPITECH PROJECT, 2022
** sdl2.hpp
** File description:
** TODO
*/

#pragma once

#include "Display.hpp"
#include "Object.hpp"
#include <map>
//#include <ncurses.h>
#include <curses.h>
#include <clocale>
#include <png.h>

#include "ArcadeError.hpp"

#include <fstream>
#include <iostream>

typedef std::string Path;
class Pixel {
public:
    int r{};
    int g{};
    int b{};
    Pixel() = default;
    virtual ~Pixel() = default;
    void ConvertPixel() {
        r *= .256;
        g *= .256;
        b *= .256;
    }
};
class Converter  {
private:
    float xFactor;
    float yFactor;
    uint height;
    uint width;
    FILE *fp;
    png_structp pngPtr;
    png_infop pngInfo;
    png_bytepp rows;
public:
    explicit Converter(const Path& Source) {
        fp = fopen(Source.c_str(), "r");
        pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        pngInfo = png_create_info_struct(pngPtr);
        png_init_io(pngPtr, fp);
        png_read_png(pngPtr, pngInfo, PNG_TRANSFORM_IDENTITY, nullptr);
        rows = png_get_rows(pngPtr, pngInfo);
        height = png_get_image_height(pngPtr, pngInfo);
        width = png_get_image_width(pngPtr, pngInfo);
        fclose(fp);
        xFactor = float(width) / float (COLS);
        yFactor = float(height) / float (LINES);
//        std::cout << height << " " << width << std::endl;
    }
    virtual ~Converter() = default;

    void processImage(Arcade::Position position);
};

namespace Arcade
{
    class ncurses: public IDisplay {
    private:
    public:
        ncurses();
        ~ncurses() override;
        Input GetInput() override;
        void ClearScreen() override;
        void RefreshScreen() override;
        void DrawObject(Object object) override;
        static void DrawTile(Tile *Tile);

        static void DrawText(Text *pText);
    };
    extern "C" ncurses *entry_point();
}