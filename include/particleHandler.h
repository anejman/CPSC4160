/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H

#include "particle.h"

class ParticleHandler
{
private:
    particle particles[MAX_PARTICLE];
    int partType;
public:
    ParticleEmitter();
    ~ParticleEmitter();

    void peInit(const char* image, SDL_Renderer* ren, int startX, int startY, int width, int height, int type);

    void peUpdate();
    void peRender(SDL_Renderer* ren);

    void quit();
};

#endif