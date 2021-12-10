/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "trident.h"

//collision check helper func
bool checkCollisionTri(SDL_Rect first_rect, SDL_Rect second_rect)
{
   int first_rect_top, first_rect_bottom, first_rect_left, first_rect_right;
   int second_rect_top, second_rect_bottom, second_rect_left, second_rect_right;

   first_rect_top = first_rect.y;
   first_rect_bottom = first_rect.y + first_rect.h;
   first_rect_left = first_rect.x;
   first_rect_right = first_rect.x + first_rect.w / 2;

   second_rect_top = second_rect.y;
   second_rect_bottom = second_rect.y + second_rect.h;
   second_rect_left = second_rect.x;
   second_rect_right = second_rect.x + second_rect.w / 2;

   if (first_rect_top > second_rect_bottom)
      return false;
   if (first_rect_bottom < second_rect_top)
      return false;
   if (first_rect_left > second_rect_right)
      return false;
   if (first_rect_right < second_rect_left)
      return false;

   return true;
}

Trident::Trident(SDL_Renderer *gameRenderer, std::vector<Tile *> wallPos)
{
   game_renderer = gameRenderer;

   walls = wallPos;

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

   int xPos, yPos;
   int validCord = false;

   while (!validCord)
   {
      std::uniform_real_distribution<double> widthDist(0, level_width - TRIDENT_WIDTH);
      std::uniform_real_distribution<double> heightDist(0, level_height - TRIDENT_HEIGHT);

      xPos = (int)widthDist(mt);
      yPos = (int)heightDist(mt);

      SDL_Rect temp = {xPos, yPos, TRIDENT_WIDTH, TRIDENT_HEIGHT};

      validCord = true;

      for (int x = 0; x < (int)walls.size(); x++)
      {
         if (checkCollisionTri(temp, walls[x]->getRect()))
         {
            validCord = false;
         }
      }
   }

   // Object Rect Dimensions and Location
   trident_rect.x = xPos;
   trident_rect.y = yPos;
   trident_rect.w = TRIDENT_WIDTH;
   trident_rect.h = TRIDENT_HEIGHT;
}

void Trident::trident_render(SDL_Rect camera_rect)
{
   SDL_Rect render_rect = {(trident_rect.x - camera_rect.x), (trident_rect.y - camera_rect.y), TRIDENT_WIDTH, TRIDENT_HEIGHT};
   SDL_RenderCopy(game_renderer, trident_texture, NULL, &render_rect);
}