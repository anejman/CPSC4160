/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "globals.h"

class ImageHandler
{
   public:
      ImageHandler(SDL_Renderer *gameRenderer);
      ~ImageHandler();

      SDL_Texture *imageHandler_load(const char *fileName);

   private:
      SDL_Renderer *game_renderer;
      SDL_Surface *image_surface;
      SDL_Texture *image_texture;
};

#endif
