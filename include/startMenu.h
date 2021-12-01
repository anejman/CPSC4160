#ifndef STARTMENU_H
#define STARTMENU_H

#include "globals.h"
#include "imageHandler.h"

class StartMenu
{
    public:
        StartMenu();
        StartMenu(SDL_Renderer *);
        ~StartMenu();
        void init();
        void hoverEffect(int state);
        void render();

    private:
        SDL_Renderer *game_renderer;
        ImageHandler *imageHandler;

        SDL_Rect background;
        SDL_Texture *backgroundTexture;
        const char *background_file = "./assets/background.png";

        SDL_Rect foreground;
        SDL_Texture *foregroundTexture;
        const char *foreground_file = "./assets/foreground.png";

        SDL_Rect title;
        SDL_Surface *titleSurface;
        SDL_Texture *titleTexture;

        SDL_Rect swapper;
        bool swapperHover;
        SDL_Surface *swapperSurface;
        SDL_Texture *swapperTexture;

        SDL_Rect start;
        bool startHover;
        SDL_Surface *startSurface;
        SDL_Texture *startTexture;

        TTF_Font *font;
        SDL_Color fontColor;
        SDL_Color hoverColor;
};

#endif