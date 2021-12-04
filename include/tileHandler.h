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
        void tileHandler_render(SDL_Rect camera_rect, int layer);
        void tileHandler_clean();

        std::vector<Tile *> getWalls() { return walls; }

    private:
        ImageHandler *imageHandler;
        SDL_Renderer *game_renderer;
        std::vector<SDL_Texture *> tile_textures;
        std::vector<vector<Tile *>> tilesets;
        std::vector<Tile *> walls;
        std::vector<const char *> map_files {"./assets/map.txt", "./assets/map2.txt", "./assets/map3.txt"};
        std::vector<const char *> tiles_files = {"./assets/tiles.png", "./assets/objTiles.png", "./assets/tiles.png"};
        int level_width = LEVEL_WIDTH;
};

#endif