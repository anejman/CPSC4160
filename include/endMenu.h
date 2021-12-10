#ifndef ENDMENU_H
#define ENDMENU_H

#include "globals.h"
#include "imageHandler.h"

class EndMenu
{
    private:
        int game_state;

        SDL_Renderer *game_renderer;
        ImageHandler *imageHandler;

        SDL_Rect background;
        SDL_Texture *backgroundTexture;
        const char *background_file = "./assets/background.png";

        SDL_Rect foreground;
        SDL_Texture *foregroundTexture;
        const char *foreground_file = "./assets/foreground.png";

        SDL_Rect title;
        SDL_Surface *titleWinSurface;
        SDL_Texture *titleWinTexture;

        SDL_Surface *titleLoseSurface;
        SDL_Texture *titleLoseTexture;

        SDL_Rect restart;
        SDL_Surface *restartSurface;
        SDL_Texture *restartTexture;
        bool restartHover;

        SDL_Surface *retrySurface;
        SDL_Texture *retryTexture;

        SDL_Rect quit;
        SDL_Surface *quitSurface;
        SDL_Texture *quitTexture;
        bool quitHover;

        TTF_Font *font;
        SDL_Color fontColor;
        SDL_Color hoverColor;

    public:
        EndMenu();

        EndMenu(SDL_Renderer *);

        ~EndMenu();

        void init();

        void setState(int val) { game_state = val; }

        void hoverEffect(int state);

        void render();
};

#endif