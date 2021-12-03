#ifndef ENEMYAI_H
#define ENEMYAI_H

#include "globals.h"
#include "imageHandler.h"
#include "spriteHandler.h"

#define SHARK_SPRITE_WIDTH 92
#define SHARK_SPRITE_HEIGHT 39
#define SHARK_SPRITE_FRAMES 3

#define SHARK_SPRITE_DURATION 200

class enemyAI
{
private:
    SDL_Renderer *aiRenderer;
    SDL_Texture *aiTexture;
    SDL_Rect aiRect;
    SDL_Rect currentFrame;
    SDL_RendererFlip flipAI;

    SpriteHandler *ai_sprite;
    ImageHandler *imageHandler;

    const char *shark_file = "./assets/sharks.png";

    int xPos;
    int yPos;
    int xVel;
    int yVel;

    int aiWidth = AI_WIDTH + AI_WIDTH;
    int aiHeight = AI_HEIGHT;

    int state;
    int guardPosX;
    int guardPosY;
    int returning;

public:
    enemyAI(SDL_Renderer *ren);
    ~enemyAI();

    void aiInit();

    void aiUpdate(SDL_Rect player);
    void aiRender(SDL_Rect camera);

    void setState(int newState);
    void setXVel(int vel);
    void setYVel(int vel);
    void setReturning(int x);

    SDL_Rect getRect() { return aiRect; }

    int getXPos() { return xPos; }
    int getYPos() { return yPos; }
};

#endif