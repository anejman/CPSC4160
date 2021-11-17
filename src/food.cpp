/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "food.h"

Food::Food(SDL_Renderer *gameRenderer)
{
   game_renderer = gameRenderer;

   food_init();
}

Food::~Food()
{
   SDL_DestroyTexture(food_texture);
}

void Food::food_init()
{
   imageHandler = new ImageHandler(game_renderer);
   food_texture = imageHandler->imageHandler_load(food_file);

   std::random_device rd;
   std::mt19937 mt(rd());

   std::uniform_real_distribution<double> widthDist(0, level_width - FOOD_WIDTH);
   std::uniform_real_distribution<double> heightDist(0, level_height - FOOD_HEIGHT);

   // Object Rect Dimensions and Location
   food_rect.x = (int)widthDist(mt);
   food_rect.y = (int)heightDist(mt);
   food_rect.w = FOOD_WIDTH;
   food_rect.h = FOOD_HEIGHT;
}

void Food::food_render(SDL_Rect camera_rect)
{
   SDL_Rect render_rect = {(food_rect.x - camera_rect.x), (food_rect.y - camera_rect.y), PLAYER_WIDTH, PLAYER_HEIGHT};
   SDL_RenderCopy(game_renderer, food_texture, NULL, &render_rect);
}