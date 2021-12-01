/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "spriteHandler.h"

SpriteHandler::SpriteHandler(int width, int height, int frames, double duration)
{
   sprite_width = width;
   sprite_height = height;
   frame_count = frames;
   frame_duration = duration;

   sprite_init();
}

SpriteHandler::~SpriteHandler() {}

void SpriteHandler::sprite_init()
{
   sprite_rect.x = 0;
   sprite_rect.y = 0;
   sprite_rect.w = sprite_width;
   sprite_rect.h = sprite_height;
   sprite_character = 0;
}

void SpriteHandler::sprite_set_sprite(int sprite_number)
{
   sprite_character = (frame_count * sprite_width * sprite_number);
}

SDL_Rect SpriteHandler::sprite_update(int frame_state)
{
   int frame_time = (int)(SDL_GetTicks() / frame_duration) % frame_count;

   sprite_rect.x = (frame_time * sprite_width) + sprite_character;
   sprite_rect.y = frame_state * sprite_height;

   return sprite_rect;
}