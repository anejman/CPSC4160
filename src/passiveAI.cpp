#include "passiveAI.h"

passiveAI::passiveAI(SDL_Renderer *ren) 
{
    aiRenderer = ren;

    aiInit();
}

passiveAI::~passiveAI() {}

void passiveAI::aiInit()
{
    imageHandler = new ImageHandler(aiRenderer);
    
    //randomizes ai model with according size
    switch(rand() % 4)
    {
        case 0:
            aiTexture = imageHandler->imageHandler_load(lightfish_file);

            aiHeight = AI_HEIGHT - AI_HEIGHT/4;
            aiWidth = AI_WIDTH;
            break;

        case 1:
            aiTexture = imageHandler->imageHandler_load(clownfish_file);

            aiHeight = AI_HEIGHT/2;
            aiWidth = AI_WIDTH/2 + AI_WIDTH/4;
            break;

        case 2:
            aiTexture = imageHandler->imageHandler_load(turtle_file);

            aiHeight = AI_HEIGHT + AI_HEIGHT/4;
            aiWidth = AI_WIDTH + AI_WIDTH/2;
            break;

        case 3:
            aiTexture = imageHandler->imageHandler_load(fish_file);

            aiHeight = AI_HEIGHT;
            aiWidth = AI_WIDTH;
            break;
    }

    flipAI = SDL_FLIP_NONE;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> widthDist(0, LEVEL_WIDTH - aiWidth);
    std::uniform_real_distribution<double> heightDist(0, LEVEL_HEIGHT - aiHeight);

    xPos = (int)widthDist(mt);
    yPos = (int)heightDist(mt);
    aiRect.w = aiWidth;
    aiRect.h = aiHeight;

    xVel = 0;
    yVel = 0;

    state = IDLE;
    wonderPos = 0;
}

void passiveAI::aiUpdate(SDL_Rect player) 
{
    switch (state)
    {
    case IDLE:
        xVel = 0;
        yVel = 0;

        if((rand() % 100) == 0)
        {
            state = WONDER;
            wonderPos = xPos;

            xVel = 2 - (rand() % 4);
            yVel = 1 - (rand() % 2);
        }
        break;
    
    case WONDER:
        if(abs(xPos - wonderPos) > WONDER_DIST)
        {
            state = IDLE;
        }

        if(xVel == 0)
        {
            state = IDLE;
        }
        break;

    case FLEE:
        if(abs(player.x - xPos) > FLEE_DIST) 
        {
            state = IDLE;
        }

        if(xVel == 0)
        {
            state = IDLE;
        }
        break;
    }

    if(xVel < 0) {
        flipAI = SDL_FLIP_HORIZONTAL;
    } else {
        flipAI = SDL_FLIP_NONE;
    }

    if(xPos > LEVEL_WIDTH) { xVel *= -2; }
    if(xPos < 0) { xVel *= -2; }
    if(yPos > LEVEL_HEIGHT) { yVel *= -2; }
    if(yPos < 0) { yVel *= -2; }

    xPos += xVel;
    yPos += yVel;

    aiRect.x = xPos;
    aiRect.y = yPos;
}

void passiveAI::aiRender(SDL_Rect camera) 
{
    SDL_Rect renderRect = {(aiRect.x - camera.x), (aiRect.y - camera.y), aiWidth, aiHeight};
    SDL_RenderCopyEx(aiRenderer, aiTexture, NULL, &renderRect, 0.0, NULL, flipAI);
}

void passiveAI::setState(int newState) 
{
    state = newState;
}

void passiveAI::setXVel(int vel)
{
    xVel = vel;
}

void passiveAI::setYVel(int vel)
{
    yVel = vel;
}