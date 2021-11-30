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
    particleHandler();
    ~particleHandler();

    void phInit(const char* image, SDL_Renderer* ren, int startX, int startY, int width, int height, int type);

    void phUpdate();
    void phRender(SDL_Renderer* ren);

    void quit();
};

#endif