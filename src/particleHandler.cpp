/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "particleHandler.h"

particle::particle() {}

particle::~particle() {}

void particle::objInit(const char *image, SDL_Renderer *ren, int x, int y, int w, int h)
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
    yPos -= 9.8 * 100 / 3600;

    if (life > 0)
    {
        objRect.x = xPos;
        objRect.y = yPos;
        objRect.w = width + width * (int)(10 * life / 100);
        objRect.h = height + height * (int)(10 * life / 100);
    }
    life--;
}

void particle::objUpdateStar()
{
    xPos += xVel;
    yPos += yVel;

    if (life > 0)
    {
        objRect.x = xPos;
        objRect.y = yPos;
        objRect.w = width;
        objRect.h = height;
    }
    life--;
}

void particle::objUpdateBubbleBump()
{
    xPos += xVel;
    yPos += yVel;

    yPos -= 9.8 * 100 / 3600;

    if (life > 0)
    {
        objRect.x = xPos;
        objRect.y = yPos;
        objRect.w = width + width * (int)(10 * life / 100);
        objRect.h = height + height * (int)(10 * life / 100);
    }
    life--;
}

void particle::objUpdateWin()
{
    xPos += xVel;
    yPos += yVel;

    if(life > 0) 
    {
        objRect.x = xPos;
        objRect.y = yPos;
        objRect.w = width;
        objRect.h = height;
    }
    life--;
}

void particle::objRenderBubble(SDL_Renderer *ren)
{
    if (life > 0)
    {
        //makes more transparent as time passes
        SDL_SetTextureAlphaMod(objGraphic, (int)255 * life / 50);
        SDL_RenderCopy(ren, objGraphic, NULL, &objRect);
    }
    else
    {
        SDL_SetTextureAlphaMod(objGraphic, 255);
    }
}

void particle::objRenderStar(SDL_Renderer *ren)
{
    if (life > 0)
    {
        SDL_SetTextureAlphaMod(objGraphic, (int)255 * life / 25);
        SDL_RenderCopy(ren, objGraphic, NULL, &objRect);
    }
    else
    {
        SDL_SetTextureAlphaMod(objGraphic, 255);
    }
}

void particle::objRenderBubbleBump(SDL_Renderer *ren)
{
    if (life > 0)
    {
        //makes more transparent as time passes
        SDL_SetTextureAlphaMod(objGraphic, (int)255 * life / 50);
        SDL_RenderCopy(ren, objGraphic, NULL, &objRect);
    }
    else
    {
        SDL_SetTextureAlphaMod(objGraphic, 255);
    }
}

void particle::objRenderWin(SDL_Renderer *ren)
{
    if (life > 0)
    {
        //randomize color
        switch(rand() % 5)
        {
            case 0:
                SDL_SetTextureColorMod(objGraphic, 234, 194, 254);
                break;
            
            case 1:
                SDL_SetTextureColorMod(objGraphic, 250, 172, 208);
                break;

            case 2:
                SDL_SetTextureColorMod(objGraphic, 255, 221, 102);
                break;

            case 3:
                SDL_SetTextureColorMod(objGraphic, 155, 255, 145);
                break;

            case 4:
                SDL_SetTextureColorMod(objGraphic, 153, 217, 234);
                break;
        }

        //makes more transparent as time passes
        SDL_SetTextureAlphaMod(objGraphic, (int)255 * life / 60);
        SDL_RenderCopy(ren, objGraphic, NULL, &objRect);
    }
    else
    {
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

particleHandler::particleHandler()
{
    partType = DEFAULT_TYPE;
}

particleHandler::~particleHandler() {}

void particleHandler::phInit(const char *image, SDL_Renderer *ren, int startX, int startY, int width, int height, int type)
{
    //check for particle type
    partType = type;
    int maxParticle = MAX_PARTICLE;

    if (partType == BUBBLE)
    {
        //sets a random velocity and lifespan for every particle
        for (int i = 0; i < maxParticle; i++)
        {
            particles.push_back(new particle);
        }

        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objInit(image, ren, startX, startY, width, height);

            particles[x]->setXVel(1 - (rand() % 2));
            particles[x]->setYVel(1 - (rand() % 5));
            particles[x]->setLife(40 + (rand() % 10));
        }
    }

    if (partType == STAR)
    {
        maxParticle = MAX_PARTICLE_STAR;

        for (int i = 0; i < maxParticle; i++)
        {
            particles.push_back(new particle);
        }

        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objInit(image, ren, startX, startY, width, height);
            particles[x]->setLife(25);

            switch (x)
            {
            case 0:
                particles[x]->setXVel(0);
                particles[x]->setYVel(-2);
                break;

            case 1:
                particles[x]->setXVel(2);
                particles[x]->setYVel(0);
                break;

            case 2:
                particles[x]->setXVel(-2);
                particles[x]->setYVel(0);
                break;

            case 3:
                particles[x]->setXVel(2);
                particles[x]->setYVel(2);
                break;

            case 4:
                particles[x]->setXVel(-2);
                particles[x]->setYVel(2);
                break;
            }
        }
    }

    if (partType == BUBBLE_BUMP)
    {
        for (int i = 0; i < maxParticle; i++)
        {
            particles.push_back(new particle);
        }

        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objInit(image, ren, startX, startY, width, height);

            particles[x]->setXVel(1 - (rand() % 2));
            particles[x]->setYVel(1 - (rand() % 2));
            particles[x]->setLife(40 + (rand() % 10));
        }
    }

    if (partType == WIN) 
    {
        maxParticle = MAX_PARTICLE_WIN;

        for (int i = 0; i < maxParticle; i++)
        {
            particles.push_back(new particle);
        }

        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objInit(image, ren, startX + (rand() % SCREEN_WIDTH), startY, width, height);

            particles[x]->setYVel(5 + (rand() % 35));
            particles[x]->setXVel(5 - (rand() % 10));
            particles[x]->setLife(50 + (rand() % 10));
        }
    }
}

void particleHandler::phUpdate()
{
    int maxParticle = MAX_PARTICLE;

    //update every particle
    if (partType == BUBBLE)
    {
        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objUpdateBubble();
        }
    }

    if (partType == STAR)
    {
        maxParticle = MAX_PARTICLE_STAR;

        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objUpdateStar();
        }
    }

    if (partType == BUBBLE_BUMP)
    {
        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objUpdateBubbleBump();
        }
    }

    if (partType == WIN) 
    {
        maxParticle = MAX_PARTICLE_WIN;

        for (int x = 0; x < maxParticle; x++) 
        {
            particles[x]->objUpdateWin();
        }
    }
}

void particleHandler::phRender(SDL_Renderer *ren)
{
    int maxParticle = MAX_PARTICLE;

    //render every particle
    if (partType == BUBBLE)
    {
        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objRenderBubble(ren);
        }
    }

    if (partType == STAR)
    {
        maxParticle = MAX_PARTICLE_STAR;

        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objRenderStar(ren);
        }
    }

    if (partType == BUBBLE_BUMP)
    {
        for (int x = 0; x < maxParticle; x++)
        {
            particles[x]->objRenderBubbleBump(ren);
        }
    }

    if (partType == WIN) 
    {
        maxParticle = MAX_PARTICLE_WIN;

        for (int x = 0; x < maxParticle; x++) 
        {
            particles[x]->objRenderWin(ren);
        }
    }
}

void particleHandler::quit()
{
    int maxParticle = MAX_PARTICLE;

    for (int x = 0; x < maxParticle; x++)
    {
        particles.clear();
    }
}