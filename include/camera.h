/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef CAMERA_H
#define CAMERA_H

#include "globals.h"

class Camera
{
   public:
      Camera();
      ~Camera();

      void camera_update(int player_x_pos, int player_y_pos);
      SDL_Rect camera_get_rect() { return camera_rect; };

   private:
      SDL_Rect camera_rect;
      int level_width = LEVEL_WIDTH;
      int level_height = LEVEL_HEIGHT;
};

#endif
