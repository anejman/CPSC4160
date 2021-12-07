#ifndef ENEMYAI_H
#define ENEMYAI_H

#include "globals.h"
#include "imageHandler.h"
#include "spriteHandler.h"
#include "tile.h"

#define SHARK_SPRITE_WIDTH 209
#define SHARK_SPRITE_HEIGHT 102
#define SHARK_SPRITE_FRAMES 2

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

    const char *shark_file = "./assets/sharksprite.png";

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

    std::vector<Tile *> walls;

public:
    enemyAI(SDL_Renderer *ren, std::vector<Tile *> wallPos);
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
    int getXVel() { return xVel; }
    int getYVel() { return yVel; }
    int getReturning() { return returning; }
};

#endif