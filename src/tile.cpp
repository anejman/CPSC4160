/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "tile.h"

Tile::Tile(int x, int y, int tile_type)
{
    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = TILE_WIDTH;
    dest_rect.h = TILE_HEIGHT;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = TILE_WIDTH;
    src_rect.h = TILE_HEIGHT;

    switch (tile_type)
    {
    case TILE_GROUND1:
        src_rect.x = 32;
        src_rect.y = 0;
        break;
    case TILE_GROUND2:
        src_rect.x = 64;
        src_rect.y = 0;
        break;
    case TILE_GROUND3:
        src_rect.x = 96;
        src_rect.y = 0;
        break;
    case TILE_GROUND4:
        src_rect.x = 128;
        src_rect.y = 0;
        break;
    case TILE_GROUND5:
        src_rect.x = 160;
        src_rect.y = 0;
        break;
    case TILE_GROUND6:
        src_rect.x = 192;
        src_rect.y = 0;
        break;
    case TILE_GROUND7:
        src_rect.x = 224;
        src_rect.y = 0;
        break;
    case TILE_ROCK1:
        src_rect.x = 0;
        src_rect.y = 32;
        break;
    case TILE_ROCK2:
        src_rect.x = 32;
        src_rect.y = 32;
        break;
    case TILE_WALLPEAK_TOPLEFT:
        src_rect.x = 96;
        src_rect.y = 128;
        break;
    case TILE_WALLPEAK_TOP:
        src_rect.x = 128;
        src_rect.y = 128;
        break;
    case TILE_WALLPEAK_TOPRIGHT:
        src_rect.x = 160;
        src_rect.y = 128;
        break;
    case TILE_WALLPEAK_LEFT:
        src_rect.x = 96;
        src_rect.y = 160;
        break;
    case TILE_WALLPEAK_CENTER:
        src_rect.x = 128;
        src_rect.y = 160;
        break;
    case TILE_WALLPEAK_RIGHT:
        src_rect.x = 160;
        src_rect.y = 160;
        break;
    case TILE_WALLPEAK_BOTTOMLEFT:
        src_rect.x = 96;
        src_rect.y = 192;
        break;
    case TILE_WALLPEAK_BOTTOMCENTER:
        src_rect.x = 128;
        src_rect.y = 192;
        break;
    case TILE_WALLPEAK_BOTTOMRIGHT:
        src_rect.x = 160;
        src_rect.y = 192;
        break;
    case TILE_WALL_LEFT:
        src_rect.x = 0;
        src_rect.y = 224;
        break;
    case TILE_WALL_CENTER:
        src_rect.x = 32;
        src_rect.y = 224;
        break;
    case TILE_WALL_RIGHT:
        src_rect.x = 64;
        src_rect.y = 224;
        break;
    case TILE_WALLBASE_LEFT:
        src_rect.x = 0;
        src_rect.y = 256;
        break;
    case TILE_WALLBASE_CENTER:
        src_rect.x = 32;
        src_rect.y = 256;
        break;
    case TILE_WALLBASE_RIGHT:
        src_rect.x = 64;
        src_rect.y = 256;
        break;
    case TILE_WALLPEAK_CORNER1:
        src_rect.x = 192;
        src_rect.y = 128;
        break;
    case TILE_WALLPEAK_CORNER2:
        src_rect.x = 224;
        src_rect.y = 128;
        break;
    case TILE_WALLPEAK_CORNER3:
        src_rect.x = 192;
        src_rect.y = 160;
        break;
    case TILE_WALLPEAK_CORNER4:
        src_rect.x = 224;
        src_rect.y = 160;
        break;
    }
}

Tile::~Tile() {}

void Tile::tile_render(SDL_Renderer *game_renderer, SDL_Texture *tile_texture, SDL_Rect camera_rect)
{
    SDL_Rect render_rect = {(dest_rect.x - camera_rect.x), (dest_rect.y - camera_rect.y), TILE_WIDTH, TILE_HEIGHT};
    SDL_RenderCopy(game_renderer, tile_texture, &src_rect, &render_rect);
}