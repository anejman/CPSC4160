#include "enemyAI.h"

enemyAI::enemyAI(SDL_Renderer *ren) 
{
    aiRenderer = ren;

    aiInit();
}

enemyAI::~enemyAI() {}

void enemyAI::aiInit()
{
    imageHandler = new ImageHandler(aiRenderer);
    aiTexture = imageHandler->imageHandler_load(shark_file);

    ai_sprite = new SpriteHandler(SHARK_SPRITE_WIDTH, SHARK_SPRITE_HEIGHT, SHARK_SPRITE_FRAMES, SHARK_SPRITE_DURATION);

    flipAI = SDL_FLIP_NONE;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> widthDist(0, LEVEL_WIDTH - aiWidth);
    std::uniform_real_distribution<double> heightDist(0, LEVEL_HEIGHT - aiHeight);

    xPos = (int)widthDist(mt);
    yPos = (int)heightDist(mt);
    aiRect.w = aiWidth;
    aiRect.h = aiHeight;

    guardPosX = xPos;
    guardPosY = yPos;

    xVel = 0;
    yVel = 0;

    state = IDLE;
    returning = 0;
}

void enemyAI::aiUpdate(SDL_Rect player) 
{
    switch (state)
    {
    case IDLE:
        xVel = 0;
        yVel = 0;

        currentFrame = ai_sprite->sprite_update(IDLE);

        if((rand() % 1000) == 0 && !returning)
        {
            state = WONDER;

            xVel = 3 - (rand() % 6);
            yVel = 3 - (rand() % 6);
        }
        break;
    
    case WONDER:
        currentFrame = ai_sprite->sprite_update(WONDER);

        if(abs(xPos - guardPosX) > (WONDER_DIST*2))
        {
            state = IDLE;
            returning = 1;
        }
        else if(abs(yPos - guardPosY) > (WONDER_DIST*2))
        {
            state = IDLE;
            returning = 1;
        }
        break;

    case ATTACK:
        currentFrame = ai_sprite->sprite_update(WONDER);

        if(abs(player.x - xPos) > ATTACK_DIST || abs(player.y - yPos) > ATTACK_DIST) 
        {
            state = IDLE;
            returning = 1;
        }

        if(abs(player.x - guardPosX) > ESCAPE_DIST || abs(player.y - guardPosY) > ESCAPE_DIST)
        {
            state = IDLE;
            returning = 1;
        }
        break;
    }

    if(returning)
    {
        if(xPos > guardPosX) { xVel = -1; }
        if(xPos < guardPosX) { xVel = 1; }
        if(yPos > guardPosY) { yVel = -1; }
        if(yPos < guardPosY) { yVel = 1; }

        if(xPos == guardPosX && yPos == guardPosY) { returning = 0; }
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

void enemyAI::aiRender(SDL_Rect camera) 
{
    SDL_Rect renderRect = {(aiRect.x - camera.x), (aiRect.y - camera.y), aiRect.w, aiRect.h};
    SDL_RenderCopyEx(aiRenderer, aiTexture, &currentFrame, &renderRect, 0.0, NULL, flipAI);
}

void enemyAI::setState(int newState) 
{
    state = newState;
}

void enemyAI::setXVel(int vel)
{
    xVel = vel;
}

void enemyAI::setYVel(int vel)
{
    yVel = vel;
}

void enemyAI::setReturning(int x)
{
    returning = x;
}