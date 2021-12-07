/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "tileHandler.h"

TileHandler::TileHandler(SDL_Renderer *gameRenderer)
{
    game_renderer = gameRenderer;

    tileHandler_init();
}

TileHandler::~TileHandler() {}

void TileHandler::tileHandler_init()
{
    imageHandler = new ImageHandler(game_renderer);
    for(int i = 0; i < LAYER_NUM; i++){
        tile_textures.push_back(imageHandler->imageHandler_load(tiles_files[i]));
    }
}

void TileHandler::tileHandler_load()
{
    std::vector<Tile *> tileset;
    int x;
    int y;
    int tile_type;

    for(int i = 0; i < LAYER_NUM; i++){

        // Tile offsets
        x = 0;
        y = 0;
        tile_type = -1;

        std::ifstream map(map_files[i]);

        if (map.fail())
        {
            std::cerr << "Error Opening Map File: " << SDL_GetError() << std::endl;
        }
        else
        {
            std::cout << "Opened Map File Successfully!" << std::endl;
        }

        while (!map.eof())
        {
            map >> tile_type;

            if (tile_type >= 0)
            {
                tileset.push_back(new Tile(x, y, tile_type, i));

                if (i == 0 && tile_type == 0)
                {
                    walls.push_back(new Tile(x, y, tile_type, i));
                }
            }

            x += TILE_WIDTH;

            if (x >= level_width)
            {
                x = 0;
                y += TILE_HEIGHT;
            }
        }

        map.close();
        tilesets.push_back(tileset);
        tileset.clear();
    }
}

void TileHandler::tileHandler_render(SDL_Rect camera_rect, int layer)
{
    for (auto tile : tilesets[layer])
    {
        tile->tile_render(game_renderer, tile_textures[layer], camera_rect);
    }
}

void TileHandler::tileHandler_clean()
{
    for(auto tileset : tilesets) 
    {
        for (auto tile : tileset)
        {
            delete tile;
        }
        tileset.clear();
    }
    tilesets.clear();
}