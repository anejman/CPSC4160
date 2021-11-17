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
const int TILE_TOPLEFT = 0;
const int TILE_TOP = 1;
const int TILE_TOPRIGHT = 2;
const int TILE_LEFT = 3;
const int TILE_CENTER = 4;
const int TILE_RIGHT = 5;
const int TILE_BOTTOMLEFT = 6;
const int TILE_BOTTOM = 7;
const int TILE_BOTTOMRIGHT = 8;

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