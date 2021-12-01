#include "pauseMenu.h"

PauseMenu::PauseMenu() {}
PauseMenu::~PauseMenu() {}

PauseMenu::PauseMenu(SDL_Renderer *renderer)
{
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
    hoverColor = {217, 190, 54};

    font = TTF_OpenFont("./assets/ShortBaby.ttf", 100);
    if (!font)
    {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }
    else
    {
        cout << "Font Loaded!" << endl;
    }
}

void PauseMenu::init()
{
    resumeHover = false;
    resumeSurface = TTF_RenderText_Solid(font, "Resume", fontColor);
    resumeTexture = SDL_CreateTextureFromSurface(game_renderer, resumeSurface);
    SDL_FreeSurface(resumeSurface);

    restartHover = false;
    restartSurface = TTF_RenderText_Solid(font, "Restart", fontColor);
    restartTexture = SDL_CreateTextureFromSurface(game_renderer, restartSurface);
    SDL_FreeSurface(restartSurface);

    quitHover = false;
    quitSurface = TTF_RenderText_Solid(font, "Quit", fontColor);
    quitTexture = SDL_CreateTextureFromSurface(game_renderer, quitSurface);
    SDL_FreeSurface(quitSurface);
}

void PauseMenu::hoverEffect(int state)
{
    switch (state)
    {
    case 1:
        if (!resumeHover)
        {
            resumeHover = true;
            SDL_DestroyTexture(resumeTexture);
            resumeSurface = TTF_RenderText_Solid(font, "Resume", hoverColor);
            resumeTexture = SDL_CreateTextureFromSurface(game_renderer, resumeSurface);
            SDL_FreeSurface(resumeSurface);
        }
        break;
    case 2:
        if (!restartHover)
        {
            restartHover = true;
            SDL_DestroyTexture(restartTexture);
            restartSurface = TTF_RenderText_Solid(font, "Restart", hoverColor);
            restartTexture = SDL_CreateTextureFromSurface(game_renderer, restartSurface);
            SDL_FreeSurface(restartSurface);
        }
        break;
    case 3:
        if (!quitHover)
        {
            quitHover = true;
            SDL_DestroyTexture(quitTexture);
            quitSurface = TTF_RenderText_Solid(font, "Quit", hoverColor);
            quitTexture = SDL_CreateTextureFromSurface(game_renderer, quitSurface);
            SDL_FreeSurface(quitSurface);
        }
        break;
    case 0:
        if (resumeHover)
        {
            resumeHover = false;
            SDL_DestroyTexture(resumeTexture);
            resumeSurface = TTF_RenderText_Solid(font, "Resume", fontColor);
            resumeTexture = SDL_CreateTextureFromSurface(game_renderer, resumeSurface);
            SDL_FreeSurface(resumeSurface);
        }
        else if (restartHover)
        {
            restartHover = false;
            SDL_DestroyTexture(restartTexture);
            restartSurface = TTF_RenderText_Solid(font, "Restart", fontColor);
            restartTexture = SDL_CreateTextureFromSurface(game_renderer, restartSurface);
            SDL_FreeSurface(restartSurface);
        }
        else if (quitHover)
        {
            quitHover = false;
            SDL_DestroyTexture(quitTexture);
            quitSurface = TTF_RenderText_Solid(font, "Quit", fontColor);
            quitTexture = SDL_CreateTextureFromSurface(game_renderer, quitSurface);
            SDL_FreeSurface(quitSurface);
        }
        break;
    default:
        break;
    }
}

void PauseMenu::render()
{
    SDL_SetRenderDrawColor(game_renderer, 89, 123, 216, 255);
    SDL_RenderFillRect(game_renderer, &menuContainer);

    SDL_RenderCopy(game_renderer, resumeTexture, NULL, &resume);
    SDL_RenderCopy(game_renderer, restartTexture, NULL, &restart);
    SDL_RenderCopy(game_renderer, quitTexture, NULL, &quit);
}
