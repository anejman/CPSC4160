/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "health.h"

Health::Health(SDL_Renderer *gameRenderer, int xpos)
{
    game_renderer = gameRenderer;
    x_pos = xpos;

    health_init();
}

Health::~Health()
{
    SDL_DestroyTexture(health_texture);
}

void Health::health_init()
{
    imageHandler = new ImageHandler(game_renderer);
    health_texture = imageHandler->imageHandler_load(health_file);

    // Object Rect Dimensions and Location
    health_rect.x = x_pos + HEALTH_X + (HEALTH_X * (x_pos / HEALTH_WIDTH));
    health_rect.y = HEALTH_Y;
    health_rect.w = HEALTH_WIDTH;
    health_rect.h = HEALTH_HEIGHT;

    // Current Frame Rect Dimensions
    current_frame.x = 0;
    current_frame.y = 0;
    current_frame.w = HEALTH_SPRITE_WIDTH;
    current_frame.h = HEALTH_SPRITE_HEIGHT;
}

void Health::health_update(int health_frame)
{
    current_frame.x = HEALTH_SPRITE_WIDTH * health_frame;
}

void Health::health_render()
{
    SDL_RenderCopy(game_renderer, health_texture, &current_frame, &health_rect);
}