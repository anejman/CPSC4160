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
        bool resumeHover;
        SDL_Surface* resumeSurface;
        SDL_Texture* resumeTexture;

        SDL_Rect restart;
        bool restartHover;
        SDL_Surface* restartSurface;
        SDL_Texture* restartTexture;

        SDL_Rect quit;
        bool quitHover;
        SDL_Surface* quitSurface;
        SDL_Texture* quitTexture;

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