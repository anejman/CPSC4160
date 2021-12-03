/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "levelEditor.h"

levelEditor::~levelEditor() {}

levelEditor::levelEditor(SDL_Renderer *gameRenderer)
{
    game_renderer = gameRenderer;
}

void levelEditor::editor_init(int x_pos, int y_pos)
{
    // Object Rect Dimensions and Location
   editor_rect.x = x_pos;
   editor_rect.y = y_pos;
   editor_rect.w = EDITOR_TILE_WIDTH;
   editor_rect.h = EDITOR_TILE_HEIGHT;
}

void levelEditor::editor_update(int new_tile_type, int layer)
{
    map_x_index = editor_rect.x  / EDITOR_TILE_WIDTH;
    map_y_index = editor_rect.y / EDITOR_TILE_HEIGHT;
    std::cout << "Position:"<<map_x_index << ": " << map_y_index << std::endl;
    
    std::ifstream map(map_files[layer]);
    std::ofstream new_map(new_map_file);
    
    if (map.fail() || new_map.fail())
    {
        std::cerr << "Error Opening Map File: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "Changed Map File Successfully!" << std::endl;
    }

    std::string line;
    int y_index_iter = 0;
    int tile_type = -1;
    
    while (!map.eof())
    {
        if(y_index_iter == map_y_index){
            for(int i = 0; i< (LEVEL_WIDTH / EDITOR_TILE_WIDTH); i++){
                map >> tile_type;

                if(i != map_x_index){
                    if(tile_type < 10)
                        new_map << "0";
                    new_map << tile_type <<" ";
                }
                else {
                    if(new_tile_type < 10)
                        new_map << "0";
                    new_map << new_tile_type <<" ";
                }
            }
        }
        else {
            getline(map,line);
            new_map << line << std::endl;
        }
        y_index_iter++;

    }
    map.close();
    new_map.close();

    std::remove(map_files[layer]);
    std::rename(new_map_file, map_files[layer]);
}

void levelEditor::editor_render(SDL_Rect camera_rect)
{
    editor_camera_x = (editor_rect.x - camera_rect.x);
    editor_camera_y = (editor_rect.y - camera_rect.y);

    SDL_Rect render_rect = { editor_camera_x, editor_camera_y, EDITOR_TILE_WIDTH, EDITOR_TILE_HEIGHT};
    
      SDL_RenderDrawRect(game_renderer, &render_rect);
}