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

    const char *lightfish_file = "./assets/lightfish.png";
    const char *clownfish_file = "./assets/clownFish.png";
    const char *turtle_file = "./assets/turtle2.png";
    const char *fish_file = "./assets/fish.png";

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