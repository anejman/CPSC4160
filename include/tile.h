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
const int TILE_GROUND1 = 0;
const int TILE_GROUND2 = 1;
const int TILE_GROUND3 = 2;
const int TILE_GROUND4 = 3;
const int TILE_GROUND5 = 4;
const int TILE_GROUND6 = 5;
const int TILE_GROUND7 = 6;
const int TILE_ROCK1 = 7;
const int TILE_ROCK2 = 8;

const int TILE_WALLPEAK_TOPLEFT = 9;
const int TILE_WALLPEAK_TOP = 10;
const int TILE_WALLPEAK_TOPRIGHT = 11;
const int TILE_WALLPEAK_LEFT = 12;
const int TILE_WALLPEAK_CENTER = 13;
const int TILE_WALLPEAK_RIGHT = 14;
const int TILE_WALLPEAK_BOTTOMLEFT = 15;
const int TILE_WALLPEAK_BOTTOMCENTER = 16;
const int TILE_WALLPEAK_BOTTOMRIGHT = 17;

const int TILE_WALL_LEFT = 18;
const int TILE_WALL_CENTER = 19;
const int TILE_WALL_RIGHT = 20;

const int TILE_WALLBASE_LEFT = 21;
const int TILE_WALLBASE_CENTER = 22;
const int TILE_WALLBASE_RIGHT = 23;

const int TILE_WALLPEAK_CORNER1 = 24;
const int TILE_WALLPEAK_CORNER2 = 25;
const int TILE_WALLPEAK_CORNER3 = 26;
const int TILE_WALLPEAK_CORNER4 = 27;

class Tile
{
    public:
        Tile(int x, int y, int tile_type);
        ~Tile();

        void tile_render(SDL_Renderer *game_renderer, SDL_Texture *tile_texture, SDL_Rect camera_rect);

    private:
        SDL_Rect dest_rect;
        SDL_Rect src_rect;
};

#endif