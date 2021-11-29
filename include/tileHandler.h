/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef TILE_HANDLER_H
#define TILE_HANDLER_H

#include "globals.h"
#include "imageHandler.h"
#include "player.h"
#include "tile.h"

class TileHandler
{
    public:
        TileHandler(SDL_Renderer *game_renderer);
        ~TileHandler();

        void tileHandler_init();
        void tileHandler_load();
        void tileHandler_render(SDL_Rect camera_rect);
        void tileHandler_clean();

    private:
        ImageHandler *imageHandler;
        SDL_Renderer *game_renderer;
        SDL_Texture *tile_texture;
        std::vector<Tile *> tileset;
        const char *tiles_file = "./assets/tiles.png";
        const char *map_file = "./assets/map.txt";
        int level_width = LEVEL_WIDTH;
};

#endif