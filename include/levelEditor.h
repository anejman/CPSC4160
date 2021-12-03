#/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "globals.h"

class levelEditor
{
    public:
        levelEditor(SDL_Renderer *gameRenderer);
        ~levelEditor();

        void editor_init(int x_pos, int y_pos);
        void editor_update(int new_tile_type, int layer);
        void editor_render(SDL_Rect camera_rect);

        // Getters
        int editor_get_x_pos() { return editor_rect.x; };
        int editor_get_y_pos() { return editor_rect.y; };
        SDL_Rect editor_get_rect() { return editor_rect; };

        // Setters
        void editor_set_x_pos(int pos) { editor_rect.x = pos; };
        void editor_set_y_pos(int pos) { editor_rect.y = pos; };

    private:
        SDL_Renderer *game_renderer;
        SDL_Rect editor_rect;
        int editor_camera_x;
        int editor_camera_y;
        std::vector<const char *> map_files {"./assets/map.txt", "./assets/map2.txt", "./assets/map3.txt"};
        const char *new_map_file = "./assets/newmap.txt";
        int map_x_index;
        int map_y_index;
};

#endif