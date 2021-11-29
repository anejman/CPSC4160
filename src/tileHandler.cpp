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
    tile_texture = imageHandler->imageHandler_load(tiles_file);
}

void TileHandler::tileHandler_load()
{

    // Tile offsets
    int x = 0;
    int y = 0;
    int tile_type = -1;

    std::ifstream map(map_file);

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
            tileset.push_back(new Tile(x, y, tile_type));
        }

        x += TILE_WIDTH;

        if (x >= level_width)
        {
            x = 0;
            y += TILE_HEIGHT;
        }
    }

    map.close();
}

void TileHandler::tileHandler_render(SDL_Rect camera_rect)
{
    for (Tile *tile : tileset)
    {
        tile->tile_render(game_renderer, tile_texture, camera_rect);
    }
}

void TileHandler::tileHandler_clean()
{
    for(auto iter : tileset)
    {
        delete iter;
    }
    tileset.clear();
}
