/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "trident.h"

Trident::Trident(SDL_Renderer *gameRenderer)
{
   game_renderer = gameRenderer;

   trident_init();
}

Trident::~Trident()
{
   SDL_DestroyTexture(trident_texture);
}

void Trident::trident_init()
{
   imageHandler = new ImageHandler(game_renderer);
   trident_texture = imageHandler->imageHandler_load(trident_file);

   std::random_device rd;
   std::mt19937 mt(rd());

   std::uniform_real_distribution<double> widthDist(0, level_width - TRIDENT_WIDTH);
   std::uniform_real_distribution<double> heightDist(0, level_height - TRIDENT_HEIGHT);

   // Object Rect Dimensions and Location
   trident_rect.x = (int)widthDist(mt);
   trident_rect.y = (int)heightDist(mt);
   trident_rect.w = TRIDENT_WIDTH;
   trident_rect.h = TRIDENT_HEIGHT;
}

void Trident::trident_render(SDL_Rect camera_rect)
{
   SDL_Rect render_rect = {(trident_rect.x - camera_rect.x), (trident_rect.y - camera_rect.y), TRIDENT_WIDTH, TRIDENT_HEIGHT};
   SDL_RenderCopy(game_renderer, trident_texture, NULL, &render_rect);
}