#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "globals.h"
#include "imageHandler.h"

class PauseMenu
{
    private:
        SDL_Renderer *game_renderer;
        ImageHandler *imageHandler;

        SDL_Rect background;
        SDL_Texture *backgroundTexture;
        const char *background_file = "./assets/background.png";

        SDL_Rect foreground;
        SDL_Texture *foregroundTexture;
        const char *foreground_file = "./assets/foreground.png";

        SDL_Rect resume;
        SDL_Surface *resumeSurface;
        SDL_Texture *resumeTexture;
        bool resumeHover;

        SDL_Rect restart;
        SDL_Surface *restartSurface;
        SDL_Texture *restartTexture;
        bool restartHover;

        SDL_Rect quit;
        SDL_Surface *quitSurface;
        SDL_Texture *quitTexture;
        bool quitHover;

        TTF_Font *font;
        SDL_Color fontColor;
        SDL_Color hoverColor;

    public:
        PauseMenu();

        PauseMenu(SDL_Renderer *);

        ~PauseMenu();

        void init();

        void hoverEffect(int state);

        void render();
};

#endif