/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include "globals.h"

class SpriteHandler
{
   public:
      SpriteHandler(int width, int height, int frames, double duration);
      ~SpriteHandler();

      void sprite_init();
      SDL_Rect sprite_update(int frame_state);

   private:
      SDL_Rect sprite_rect;
      int sprite_width;
      int sprite_height;
      int sprite_frame = 0;
      int frame_count;
      double frame_duration;
};

#endif
