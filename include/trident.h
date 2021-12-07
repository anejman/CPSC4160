/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef TRIDENT_H
#define TRIDENT_H

#include "globals.h"
#include "imageHandler.h"
#include "tile.h"

class Trident
{
   public:
      Trident(SDL_Renderer *tridentRenderer, std::vector<Tile *> wallPos);
      ~Trident();

      void trident_init();
      void trident_render(SDL_Rect camera_rect);
      SDL_Rect trident_get_rect() { return trident_rect; };

   private:
      ImageHandler *imageHandler;
      SDL_Renderer *game_renderer;
      SDL_Texture *trident_texture;
      SDL_Rect trident_rect;
      const char *trident_file = "./assets/trident.png";
      int level_width = LEVEL_WIDTH;
      int level_height = LEVEL_HEIGHT;
      std::vector<Tile *> walls;
};

#endif
