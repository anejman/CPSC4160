/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "imageHandler.h"

ImageHandler::ImageHandler(SDL_Renderer *gameRenderer)
{
   game_renderer = gameRenderer;
}

ImageHandler::~ImageHandler()
{
   SDL_DestroyTexture(image_texture);
}

SDL_Texture *ImageHandler::imageHandler_load(const char *fileName)
{
   image_surface = IMG_Load(fileName);

   SDL_SetColorKey( image_surface, SDL_TRUE, SDL_MapRGB( image_surface->format, 0, 0xFF, 0xFF ) );

   image_texture = SDL_CreateTextureFromSurface(game_renderer, image_surface);

   SDL_FreeSurface(image_surface);

   if (!image_texture)
   {
      std::cerr << "Error Loading Texture!" << std::endl;
   }

   return image_texture;
}