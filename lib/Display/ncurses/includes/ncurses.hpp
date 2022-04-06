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

    /**
     * Pixel constructor
     */
    Pixel() = default;

    /**
     * Pixel destructor
     */
    virtual ~Pixel() = default;

    /**
     * This function converts a ncursses color to a pixel color.
     */
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
    /**
     * It reads the PNG file and stores the pixel data in rows
     *
     * @param Path The path to the image file.
     *
     * @return Nothing.
     */
    explicit Converter(const Path& Source) {
        fp = fopen(Source.c_str(), "r");
        pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!pngPtr)
            return;
        pngInfo = png_create_info_struct(pngPtr);
        png_init_io(pngPtr, fp);
        png_read_png(pngPtr, pngInfo, PNG_TRANSFORM_IDENTITY, nullptr);
        rows = png_get_rows(pngPtr, pngInfo);
        height = png_get_image_height(pngPtr, pngInfo);
        width = png_get_image_width(pngPtr, pngInfo);
        fclose(fp);
        xFactor = float(width) / float (COLS);
        yFactor = float(height) / float (LINES);
    }

    /**
     * This is the destructor
     */
    virtual ~Converter() = default;

    /**
     * Drawing the image on the screen.
     * @param Arcade::Position The position of the image.
     */
    void processImage(Arcade::Position position);
};

namespace Arcade
{
    class ncurses: public IDisplay {
    private:
    public:
        /**
         * A library that allows you to use the ncurses library.
         */
        ncurses();

        /**
         * Overriding the destructor of the base class.
         */
        ~ncurses() override;

        /**
         * Returning the input from the user.
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
         * A function that draws the object on the screen.
         * @param Object is the object to draw.
         */
        void DrawObject(Object object) override;

        /**
         * A function that draws the tile on the screen.
         * @param Tile is the tile to draw.
         */
        static void DrawTile(Tile *Tile);

        /**
         * A function that draws the text on the screen.
         * @param Text is the text to draw.
         */
        static void DrawText(Text *pText);
    };
    extern "C" ncurses *entry_point();
}