/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "particleHandler.h"

ParticleHandler::ParticleHandler(SDL_Renderer* gameRenderer, SDL_Texture* particleTexture, int width, int height, int alpha, int life)
{
    game_renderer = gameRenderer;
    particle_texture = particleTexture;
    particle_alpha = alpha;
    particle_life = life;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> xpd(0, 64);
    std::uniform_real_distribution<double> ypd(0, 64); 

    x_pos_dist = (int)xpd(mt);
    y_pos_dist = (int)ypd(mt);

    particle_rect.x = x_pos_dist;
    particle_rect.y = y_pos_dist;
    particle_rect.w = width;
    particle_rect.h = height;
}

ParticleHandler::~ParticleHandler() {}

void ParticleHandler::particleHandler_render(int x_pos, int y_pos)
{   
    particle_rect.x = x_pos_dist + x_pos;
    particle_rect.y = y_pos_dist + y_pos;
   
    SDL_SetTextureAlphaMod(particle_texture, particle_alpha);

    SDL_RenderCopy(game_renderer, particle_texture, NULL, &particle_rect);

    particle_frame++;
}

bool ParticleHandler::isDead()
{
    return particle_frame > particle_life;
}