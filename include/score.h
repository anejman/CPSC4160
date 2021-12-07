#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "globals.h"

using namespace std;

class Score
{
    private:
        int score;

        SDL_Surface *text_surface;
        SDL_Texture *text_texture;
        SDL_Rect text_rect;

        SDL_Surface *label_surface;
        SDL_Texture *label_texture;
        SDL_Rect label_rect;
        const char *label;

        SDL_Renderer *game_renderer;

        TTF_Font *label_font;
        TTF_Font *score_font;
        SDL_Color fontColor;

    public:
        Score(SDL_Renderer *);

        void init();

        bool increment()
        {
            score += 1;
            updateTexture();
            
            return (score == 5);
        }

        void updateTexture();

        void resetScore()
        {
            score = 0;
            updateTexture();
        }

        void render();
};

#endif