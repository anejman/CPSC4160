#ifndef PASSIVEAI_H
#define PASSIVEAI_H

#include "globals.h"
#include "imageHandler.h"
#include "spriteHandler.h"

#define TURTLE_SPRITE_WIDTH 306
#define TURTLE_SPRITE_HEIGHT 216
#define TURTLE_SPRITE_FRAMES 2

#define WHALE_SPRITE_WIDTH 320
#define WHALE_SPRITE_HEIGHT 242
#define WHALE_SPRITE_FRAMES 4

#define CLOWN_SPRITE_WIDTH 245
#define CLOWN_SPRITE_HEIGHT 167
#define CLOWN_SPRITE_FRAMES 2

#define LIGHT_SPRITE_WIDTH 701
#define LIGHT_SPRITE_HEIGHT 477
#define LIGHT_SPRITE_FRAMES 2

#define AI_SPRITE_DURATION 100

class passiveAI
{
private:
    SDL_Renderer *aiRenderer;
    SDL_Texture *aiTexture;
    SDL_Rect aiRect;
    SDL_Rect currentFrame;
    SDL_RendererFlip flipAI;

    SpriteHandler *ai_sprite;
    ImageHandler *imageHandler;

    const char *lightfish_file = "./assets/lightfishs.png";
    const char *clownfish_file = "./assets/clownfishs.png";
    const char *turtle_file = "./assets/turtles.png";
    const char *whale_file = "./assets/whales.png";

    int xPos;
    int yPos;
    int xVel;
    int yVel;

    int aiWidth = AI_WIDTH;
    int aiHeight = AI_HEIGHT;

    int state;
    int wonderPos;

public:
    passiveAI(SDL_Renderer *ren);
    ~passiveAI();

    void aiInit();

    void aiUpdate(SDL_Rect player);
    void aiRender(SDL_Rect camera);

    void setState(int newState);
    void setXVel(int vel);
    void setYVel(int vel);

    SDL_Rect getRect() { return aiRect; }
};

#endif