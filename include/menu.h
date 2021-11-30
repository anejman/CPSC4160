#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

class GameMenu {

    private:
        SDL_Rect menuContainer;
        SDL_Renderer* game_renderer;

        vector<string> options;

        SDL_Rect resume;
        SDL_Surface* resumeSurface;
        SDL_Texture* resumeTexture;
        bool resumeHover;

        SDL_Rect restart;
        SDL_Surface* restartSurface;
        SDL_Texture* restartTexture;
        bool restartHover;

        SDL_Rect quit;
        SDL_Surface* quitSurface;
        SDL_Texture* quitTexture;
        bool quitHover;

        TTF_Font* font;
        SDL_Color fontColor;
        SDL_Color hoverColor;

    public:

        GameMenu();

        GameMenu(SDL_Renderer*);

        ~GameMenu();

        void init();

        void hoverEffect(int state);

        void render();

};




#endif