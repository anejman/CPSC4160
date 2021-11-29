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

        SDL_Rect restart;
        SDL_Surface* restartSurface;
        SDL_Texture* restartTexture;

        SDL_Rect quit;
        SDL_Surface* quitSurface;
        SDL_Texture* quitTexture;

        SDL_Color fontColor;
        TTF_Font* font;

    public:

        GameMenu();

        GameMenu(SDL_Renderer*);

        ~GameMenu();

        void init();

        void handleInput();

        void render();

};




#endif