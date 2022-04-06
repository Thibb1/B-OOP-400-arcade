# Arcade
Arcade is a gaming platform, a program that lets the user choose a game to play and keeps a register of player scores.
To be able to deal with the elements of your gaming plateform at run-time, your graphics libraries and your games must be implemented as dynamic libraries, loaded at run-time.

## Interface Sharing

- [Thomas Gireaudot](thomas.gireaudot@epitech.eu) (thomas.gireaudot@epitech.eu)
## Documentation

[![](https://img.shields.io/badge/Documentation-pdf-red.svg)](./doc/refman.pdf)

## Requirements

`Build`
- C++20 compiler
- cmake 3.17

`Libraries`
- SFML
- SDL
- SDL_image
- SDL_mixer
- SDL_ttf
- NCURSES

## Build

```
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Librairies
### Graphic
We include `3` graphic libs:
- SFML
- SDL
- NCURSES

### Game
We include `2` game libs:
- Nibbler
- Pacman

## Usage
```bash
USAGE:
  ./arcade path_to_graphical_lib

DESCRIPTION:
  lib         path to the initial graphical library to load ./lib/arcade_(sfml|ncurses|sdl2).so

COMMANDS:
  N           next graphic lib
  P           previous graphic lib
  F           next game lib
  B           previous game lib

  M           menu
  R           reset the game
  ESC         close arcade

  RIGHT_ARROW move right
  LEFT_ARROW  move left
  UP_ARROW    move up
  DOWN_ARROW  move down
```
