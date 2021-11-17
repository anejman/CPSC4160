/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef FOOD_H
#define FOOD_H

#include "globals.h"
#include "imageHandler.h"

class Food
{
   public:
      Food(SDL_Renderer *foodRenderer);
      ~Food();

      void food_init();
      void food_render(SDL_Rect camera_rect);
      SDL_Rect food_get_rect() { return food_rect; };

   private:
      ImageHandler *imageHandler;
      SDL_Renderer *game_renderer;
      SDL_Texture *food_texture;
      SDL_Rect food_rect;
      const char *food_file = "./assets/seed.png";
      int level_width = LEVEL_WIDTH;
      int level_height = LEVEL_HEIGHT;
};

#endif
