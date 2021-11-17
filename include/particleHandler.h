/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H

#include "globals.h"

class ParticleHandler
{
   public:
        //Initialize position and animation
        ParticleHandler(SDL_Renderer* gameRenderer, SDL_Texture* particleTexture, int width, int height, int alpha, int life);
        ~ParticleHandler();

        //Shows the particle
        void particleHandler_render(int x_pos, int y_pos);

        //Checks if particle is dead
        bool isDead();

   private:
        SDL_Renderer* game_renderer;
        SDL_Texture* particle_texture;
        SDL_Rect particle_rect;

        int x_pos_dist;
        int y_pos_dist;
        int particle_alpha;
        int particle_life;
        int particle_frame = 0;
};

#endif