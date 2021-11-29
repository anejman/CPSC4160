#include "menu.h"
#include "globals.h"

GameMenu::GameMenu() {}
GameMenu::~GameMenu() {}

GameMenu::GameMenu(SDL_Renderer* renderer) {
    game_renderer = renderer;

    menuContainer.x = 0;
    menuContainer.y = 0;
    menuContainer.w = SCREEN_WIDTH;
    menuContainer.h = SCREEN_HEIGHT;
    
    resume.x = MENU_ITEM_X;
    resume.y = RESUME_Y;
    resume.w = 200;
    resume.h = 50;

    restart.x = MENU_ITEM_X;
    restart.y = RESTART_Y;
    restart.w = 200;
    restart.h = 50;

    quit.x = MENU_ITEM_X + 40;
    quit.y = QUIT_Y;
    quit.w = 120;
    quit.h = 50;

    fontColor = {255, 255, 255};

    if ( TTF_Init() < 0 ) {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
    }

    font = TTF_OpenFont("./assets/Aquino.ttf", 15);
    if ( !font ) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }
}

void GameMenu::init() {
    resumeSurface = TTF_RenderText_Solid(font, "Resume", fontColor);
    resumeTexture = SDL_CreateTextureFromSurface(game_renderer, resumeSurface);

    restartSurface = TTF_RenderText_Solid(font, "Restart", fontColor);
    restartTexture = SDL_CreateTextureFromSurface(game_renderer, restartSurface);

    quitSurface = TTF_RenderText_Solid(font, "Quit", fontColor);
    quitTexture = SDL_CreateTextureFromSurface(game_renderer, quitSurface);
}

void GameMenu::render() {
    SDL_SetRenderDrawColor(game_renderer, 89, 123, 216, 255);
    SDL_RenderFillRect(game_renderer, &menuContainer);

    SDL_RenderCopy(game_renderer, resumeTexture, NULL, &resume);
    SDL_RenderCopy(game_renderer, restartTexture, NULL, &restart);
    SDL_RenderCopy(game_renderer, quitTexture, NULL, &quit);

}

