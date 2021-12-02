#ifndef PASSIVEAI_H
#define PASSIVEAI_H

#include "globals.h"
#include "imageHandler.h"

class passiveAI
{
private:
    SDL_Renderer *aiRenderer;
    SDL_Texture *aiTexture;
    SDL_Rect aiRect;
    SDL_RendererFlip flipAI;

    ImageHandler *imageHandler;

    const char *ai_file = "./assets/star.png";

    int xPos;
    int yPos;
    int xVel;
    int yVel;

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