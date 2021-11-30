/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "particleHandler.h"

particle::particle() {}

particle::~particle() {}

void particle::objInit(const char* image, SDL_Renderer* ren, int x, int y, int w, int h)
{
    objRender = ren;

    imageHandler = new ImageHandler(objRender);

    //load particle image
    objGraphic = imageHandler->imageHandler_load(image);

    xPos = x;
    yPos = y;

    width = w;
    height = h;

    xVel = 0;
    yVel = 0;
}

void particle::objUpdateBubble()
{
    //move particle
    xPos += xVel;
    yPos += yVel;

    //makes bubble move upwards
    yPos -= 9.8*100/3600;

    if(life > 0) {
        objRect.x = xPos;
        objRect.y = yPos;
        objRect.w = width + width * (int)(10*life/100);
        objRect.h = height + height * (int)(10*life/100);
    }
    life--;
}

void particle::objRenderBubble(SDL_Renderer* ren)
{
    if(life > 0) {
        //makes more transparent as time passes
        SDL_SetTextureAlphaMod(objGraphic, (int)255*life/30);
        SDL_RenderCopy(ren, objGraphic, NULL, &objRect);
    } else {
        SDL_SetTextureAlphaMod(objGraphic, 255);
    }
}

void particle::quit()
{
    SDL_DestroyTexture(objGraphic);
}

void particle::setXVel(int x)
{
    xVel = x;
}

void particle::setYVel(int y)
{
    yVel = y;
}

void particle::setXPos(int x)
{
    xPos = x;
}

void particle::setYPos(int y)
{
    yPos = y;
}

void particle::setLife(int newLife)
{
    life = newLife;
}

/*=======================================Particle Handler Section==========================*/

particleHandler::particleHandler() {}

particleHandler::~particleHandler() {}

void particleHandler::phInit(const char* image, SDL_Renderer* ren, int startX, int startY, int width, int height, int type)
{
    //check for particle type
    partType = type;
    int maxParticle = MAX_PARTICLE;

    if(partType == BUBBLE) {
        //sets a random velocity and lifespan for every particle
        for(int x = 0; x < maxParticle; x++) {
            particles[x].objInit(image, ren, startX, startY, width, height);

            particles[x].setXVel(5 - (rand() % 10));
            particles[x].setYVel(5 - (rand() % 10));
            particles[x].setLife(5 + (rand() % 10));
        }
    }
}

void particleHandler::phUpdate() 
{
    int maxParticle = MAX_PARTICLE;

    //update every particle
    if(partType == BUBBLE) {
        for(int x = 0; x < maxParticle; x++) {
            particles[x].objUpdateBubble();
        }
    }
}

void particleHandler::phRender(SDL_Renderer* ren) 
{
    int maxParticle = MAX_PARTICLE;

    //render every particle
    if(partType == BUBBLE) {
        for(int x = 0; x < maxParticle; x++) {
            particles[x].objRenderBubble(ren);
        }
    }
}

void particleHandler::quit() 
{
    int maxParticle = MAX_PARTICLE;

    for(int x = 0; x < maxParticle; x++) {
        particles[x].quit();
    }
}