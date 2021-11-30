#include "score.h"

Score::Score(SDL_Renderer* renderer) {

    game_renderer = renderer;

    fontColor = {255, 255, 255};

    score = 0;

    label_rect.x = SCORE_X + 19;
    label_rect.y = SCORE_Y;
    label_rect.w = 66;
    label_rect.h = 32;

    text_rect.x = SCORE_X;
    text_rect.y = SCORE_Y;
    text_rect.w = 18;
    text_rect.h = 30;

    label_font = TTF_OpenFont("./assets/ShortBaby.ttf", 35);
    if ( !label_font ) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    } else {
        cout << "Font Loaded!" << endl;
    }
    score_font = TTF_OpenFont("./assets/ShortBaby.ttf", 45);
    if ( !score_font ) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    } else {
        cout << "Font Loaded!" << endl;
    }
}

void Score::init() {

    label = " of 5";
    label_surface = TTF_RenderText_Solid(label_font, label, fontColor);
    label_texture = SDL_CreateTextureFromSurface(game_renderer, label_surface);


    string score_string = to_string(score);
    const char* score_message = score_string.c_str();

    cout << "Score: " << score_message << endl;

    text_surface = TTF_RenderText_Solid(score_font, score_message, fontColor);
    text_texture = SDL_CreateTextureFromSurface(game_renderer, text_surface);
    
}

void Score::updateTexture() {
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    string score_string = to_string(score);
    const char* score_message = score_string.c_str();

    cout << "Score: " << score_message << endl;

    text_surface = TTF_RenderText_Solid(score_font, score_message, fontColor);
    text_texture = SDL_CreateTextureFromSurface(game_renderer, text_surface);
}

void Score::render() {
    SDL_RenderCopy(game_renderer, label_texture, NULL, &label_rect);
    SDL_RenderCopy(game_renderer, text_texture, NULL, &text_rect);
}