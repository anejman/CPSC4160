#ifndef PARTICLE_H
#define PARTICLE_H

#include "globals.h"
#include "imageHandler.h"

class particle
{
    private:
        SDL_Renderer *objRender;
        SDL_Texture *objGraphic;
        SDL_Rect objRect;

        ImageHandler *imageHandler;

        int xPos;
        int yPos;
        int xVel;
        int yVel;

        int width;
        int height;

        int life;

    public:
        particle();
        ~particle();

        void objInit(const char *image, SDL_Renderer *ren, int x, int y, int w, int h);
        void quit();

        void objUpdateBubble();
        void objUpdateStar();
        void objUpdateBubbleBump();
        void objUpdateBlood();
        void objUpdateWin();

        void objRenderBubble(SDL_Renderer *ren);
        void objRenderStar(SDL_Renderer *ren);
        void objRenderBubbleBump(SDL_Renderer *ren);
        void objRenderBlood(SDL_Renderer *ren);
        void objRenderWin(SDL_Renderer *ren);

        void setXVel(int x);
        void setYVel(int y);
        void setXPos(int x);
        void setYPos(int y);
        void setLife(int newLife);

        int getXVel() { return xVel; }
        int getYVel() { return yVel; }
        int getXPos() { return xPos; }
        int getYPos() { return yPos; }
        int getLife() { return life; }
};

#endif