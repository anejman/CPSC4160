/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef TILE_H
#define TILE_H

#include "globals.h"

// Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

// The different tile sprites
const int TILE_EMPTY = 0;

const int TILE_GROUND1 = 1;
const int TILE_GROUND2 = 2;
const int TILE_GROUND3 = 3;
const int TILE_GROUND4 = 4;
const int TILE_GROUND5 = 5;
const int TILE_GROUND6 = 6;
const int TILE_GROUND7 = 7;
const int TILE_ROCK1 = 8;
const int TILE_ROCK2 = 9;

const int TILE_WALL_LEFT = 10;
const int TILE_WALL_CENTER = 11;
const int TILE_WALL_RIGHT = 12;
const int TILE_WALLBASE_LEFT = 13;
const int TILE_WALLBASE_CENTER = 14;
const int TILE_WALLBASE_RIGHT = 15;

const int TILE_WALLPEAK_TOPLEFT = 1;
const int TILE_WALLPEAK_TOP = 2;
const int TILE_WALLPEAK_TOPRIGHT = 3;
const int TILE_WALLPEAK_LEFT = 4;
const int TILE_WALLPEAK_CENTER = 5;
const int TILE_WALLPEAK_RIGHT = 6;
const int TILE_WALLPEAK_BOTTOMLEFT = 7;
const int TILE_WALLPEAK_BOTTOMCENTER = 8;
const int TILE_WALLPEAK_BOTTOMRIGHT = 9;

const int TILE_WALLPEAK_CORNER1 = 10;
const int TILE_WALLPEAK_CORNER2 = 11;
const int TILE_WALLPEAK_CORNER3 = 12;
const int TILE_WALLPEAK_CORNER4 = 13;

const int OBJTILE_SEEWEED = 1;
const int OBJTILE_SEEWEED2 = 2;
const int OBJTILE_CORAL = 3;
const int OBJTILE_CORAL2 = 4;
const int OBJTILE_CORAL3 = 5;
const int OBJTILE_CORAL4 = 6;
const int OBJTILE_BIGCORAL = 7;
const int OBJTILE_BIGCORAL2 = 8;
const int OBJTILE_BIGCORAL3 = 9;
const int OBJTILE_BIGCORAL4 = 10;
const int OBJTILE_SHELL = 11;
const int OBJTILE_SHELL2 = 12;
const int OBJTILE_SHELL3 = 13;
const int OBJTILE_SHELL4 = 14;
const int OBJTILE_STARFISH = 15;

class Tile
{
    public:
        Tile(int x, int y, int tile_type, int layer);
        ~Tile();

        void tile_render(SDL_Renderer *game_renderer, SDL_Texture *tile_texture, SDL_Rect camera_rect);

    private:
        SDL_Rect dest_rect;
        SDL_Rect src_rect;
};

#endif