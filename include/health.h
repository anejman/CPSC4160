/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef HEALTH_H
#define HEALTH_H

#include "globals.h"
#include "imageHandler.h"

#define HEALTH_SPRITE_WIDTH 17
#define HEALTH_SPRITE_HEIGHT 17
#define HEALTH_SPRITE_FRAMES 5
#define HEALTH_SPRITE_DURATION 250

class Health
{
   public:
      Health(SDL_Renderer *healthRenderer, int xpos);
      ~Health();

      void health_init();
      void health_update(int health_frame);
      void health_render();

   private:
      ImageHandler *imageHandler;
      SDL_Renderer *game_renderer;
      SDL_Texture *health_texture;
      SDL_Rect health_rect;
      SDL_Rect current_frame;
      const char *health_file = "./assets/health.png";
      int x_pos;
};

#endif
