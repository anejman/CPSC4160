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
    case TILE_TOPLEFT:
        src_rect.x = 0;
        src_rect.y = 32;
        break;
    case TILE_TOP:
        src_rect.x = 16;
        src_rect.y = 32;
        break;
    case TILE_TOPRIGHT:
        src_rect.x = 32;
        src_rect.y = 32;
        break;
    case TILE_LEFT:
        src_rect.x = 0;
        src_rect.y = 48;
        break;
    case TILE_CENTER:
        src_rect.x = 16;
        src_rect.y = 48;
        break;
    case TILE_RIGHT:
        src_rect.x = 32;
        src_rect.y = 48;
        break;
    case TILE_BOTTOMLEFT:
        src_rect.x = 0;
        src_rect.y = 64;
        break;
    case TILE_BOTTOM:
        src_rect.x = 16;
        src_rect.y = 64;
        break;
    case TILE_BOTTOMRIGHT:
        src_rect.x = 32;
        src_rect.y = 64;
        break;
    }
}

Tile::~Tile() {}

void Tile::tile_render(SDL_Renderer *game_renderer, SDL_Texture *tile_texture, SDL_Rect camera_rect)
{
    SDL_Rect render_rect = {(dest_rect.x - camera_rect.x), (dest_rect.y - camera_rect.y), TILE_WIDTH, TILE_HEIGHT};
    SDL_RenderCopy(game_renderer, tile_texture, &src_rect, &render_rect);
}