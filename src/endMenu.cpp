#include "endMenu.h"

EndMenu::EndMenu(SDL_Renderer* renderer)
{
    game_renderer = renderer;

    game_state = 0;

    background.x = 0;
    background.y = 0;
    background.w = SCREEN_WIDTH;
    background.h = SCREEN_HEIGHT;

    foreground.x = 0;
    foreground.y = 0;
    foreground.w = SCREEN_WIDTH;
    foreground.h = SCREEN_HEIGHT;

    title.x = 145;
    title.y = TITLE_Y + 60;
    title.w = 350;
    title.h = 80;

    restart.x = MENU_ITEM_X - 25;
    restart.y = RESTART_Y + 60;
    restart.w = 250;
    restart.h = 50;

    quit.x = MENU_ITEM_X + 50;
    quit.y = QUIT_Y + 60;
    quit.w = 100;
    quit.h = 40;

    fontColor = WHITE;
    hoverColor = HOVER_COLOR;

    if (TTF_Init() < 0)
    {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("./assets/ShortBaby.ttf", 100);
    if (!font)
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

void EndMenu::init()
{
    imageHandler = new ImageHandler(game_renderer);
    backgroundTexture = imageHandler->imageHandler_load(background_file);
    foregroundTexture = imageHandler->imageHandler_load(foreground_file);

    titleWinSurface = TTF_RenderText_Solid(font, "You Win", fontColor);
    titleWinTexture = SDL_CreateTextureFromSurface(game_renderer, titleWinSurface);
    SDL_FreeSurface(titleWinSurface);

    titleLoseSurface = TTF_RenderText_Solid(font, "Game Over", fontColor);
    titleLoseTexture = SDL_CreateTextureFromSurface(game_renderer, titleLoseSurface);
    SDL_FreeSurface(titleLoseSurface);

    restartHover = false;
    restartSurface = TTF_RenderText_Solid(font, "Play Again", fontColor);
    restartTexture = SDL_CreateTextureFromSurface(game_renderer, restartSurface);
    SDL_FreeSurface(restartSurface);

    retrySurface = TTF_RenderText_Solid(font, "Try Again", fontColor);
    retryTexture = SDL_CreateTextureFromSurface(game_renderer, retrySurface);
    SDL_FreeSurface(retrySurface);

    quitHover = false;
    quitSurface = TTF_RenderText_Solid(font, "Quit", fontColor);
    quitTexture = SDL_CreateTextureFromSurface(game_renderer, quitSurface);
    SDL_FreeSurface(quitSurface);
}

void EndMenu::hoverEffect(int state) {
    switch (state)
    {
    case 1:
        if (!restartHover)
        {
            restartHover = true;

            if (game_state == 0) {
                SDL_DestroyTexture(retryTexture);
                retrySurface = TTF_RenderText_Solid(font, "Try Again", hoverColor);
                retryTexture = SDL_CreateTextureFromSurface(game_renderer, retrySurface);
                SDL_FreeSurface(retrySurface);
            } else {
                SDL_DestroyTexture(restartTexture);
                restartSurface = TTF_RenderText_Solid(font, "Play Again", hoverColor);
                restartTexture = SDL_CreateTextureFromSurface(game_renderer, restartSurface);
                SDL_FreeSurface(restartSurface);
            }
            
        }
        break;
    case 2:
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
        if (restartHover)
        {
            restartHover = false;
            if (game_state == 0) {
                SDL_DestroyTexture(retryTexture);
                retrySurface = TTF_RenderText_Solid(font, "Try Again", fontColor);
                retryTexture = SDL_CreateTextureFromSurface(game_renderer, retrySurface);
                SDL_FreeSurface(retrySurface);
            } else {
                SDL_DestroyTexture(restartTexture);
                restartSurface = TTF_RenderText_Solid(font, "Play Again", fontColor);
                restartTexture = SDL_CreateTextureFromSurface(game_renderer, restartSurface);
                SDL_FreeSurface(restartSurface);
            }
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

void EndMenu::render() {
    SDL_RenderCopy(game_renderer, backgroundTexture, NULL, &background);
    SDL_RenderCopy(game_renderer, foregroundTexture, NULL, &foreground);

    if (game_state == 0) {
        SDL_RenderCopy(game_renderer, titleLoseTexture, NULL, &title);
        SDL_RenderCopy(game_renderer, retryTexture, NULL, &restart);
    } else {
        SDL_RenderCopy(game_renderer, titleWinTexture, NULL, &title);
        SDL_RenderCopy(game_renderer, restartTexture, NULL, &restart);
    }
    
    SDL_RenderCopy(game_renderer, quitTexture, NULL, &quit);
}