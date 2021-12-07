#include "startMenu.h"

StartMenu::StartMenu(SDL_Renderer *renderer)
{
    game_renderer = renderer;

    background.x = 0;
    background.y = 0;
    background.w = SCREEN_WIDTH;
    background.h = SCREEN_HEIGHT;

    foreground.x = 0;
    foreground.y = 0;
    foreground.w = SCREEN_WIDTH;
    foreground.h = SCREEN_HEIGHT;

    title.x = (SCREEN_WIDTH / 2 - 200);
    title.y = TITLE_Y;
    title.w = 400;
    title.h = 100;

    swapper.x = (SCREEN_WIDTH / 2 - 100);
    swapper.y = SWAPPER_Y;
    swapper.w = 200;
    swapper.h = 50;

    start.x = (SCREEN_WIDTH / 2 - 100);
    start.y = START_Y;
    start.w = 200;
    start.h = 50;

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

StartMenu::~StartMenu() {}

void StartMenu::init()
{
    imageHandler = new ImageHandler(game_renderer);
    backgroundTexture = imageHandler->imageHandler_load(background_file);
    foregroundTexture = imageHandler->imageHandler_load(foreground_file);

    titleSurface = TTF_RenderText_Solid(font, "Atlantean Adventure", fontColor);
    titleTexture = SDL_CreateTextureFromSurface(game_renderer, titleSurface);
    SDL_FreeSurface(titleSurface);

    swapperHover = false;
    swapperSurface = TTF_RenderText_Solid(font, "Change Character", fontColor);
    swapperTexture = SDL_CreateTextureFromSurface(game_renderer, swapperSurface);
    SDL_FreeSurface(swapperSurface);

    startHover = false;
    startSurface = TTF_RenderText_Solid(font, "Start", fontColor);
    startTexture = SDL_CreateTextureFromSurface(game_renderer, startSurface);
    SDL_FreeSurface(startSurface);
}

void StartMenu::hoverEffect(int state)
{
    switch (state)
    {
    case 1:
        if (!startHover)
        {
            startHover = true;
            SDL_DestroyTexture(startTexture);
            startSurface = TTF_RenderText_Solid(font, "Start", hoverColor);
            startTexture = SDL_CreateTextureFromSurface(game_renderer, startSurface);
            SDL_FreeSurface(startSurface);
        }
        break;
    case 2:
        if (!swapperHover)
        {
            swapperHover = true;
            SDL_DestroyTexture(swapperTexture);
            swapperSurface = TTF_RenderText_Solid(font, "Change Character", hoverColor);
            swapperTexture = SDL_CreateTextureFromSurface(game_renderer, swapperSurface);
            SDL_FreeSurface(swapperSurface);
        }
        break;
    case 0:
        if (startHover)
        {
            startHover = false;
            SDL_DestroyTexture(startTexture);
            startSurface = TTF_RenderText_Solid(font, "Start", fontColor);
            startTexture = SDL_CreateTextureFromSurface(game_renderer, startSurface);
            SDL_FreeSurface(startSurface);
        }
        else if (swapperHover)
        {
            swapperHover = false;
            SDL_DestroyTexture(swapperTexture);
            swapperSurface = TTF_RenderText_Solid(font, "Change Character", fontColor);
            swapperTexture = SDL_CreateTextureFromSurface(game_renderer, swapperSurface);
            SDL_FreeSurface(swapperSurface);
        }
        break;
    default:
        break;
    }
}

void StartMenu::render()
{
    SDL_RenderCopy(game_renderer, backgroundTexture, NULL, &background);
    SDL_RenderCopy(game_renderer, foregroundTexture, NULL, &foreground);
    SDL_RenderCopy(game_renderer, titleTexture, NULL, &title);
    SDL_RenderCopy(game_renderer, swapperTexture, NULL, &swapper);
    SDL_RenderCopy(game_renderer, startTexture, NULL, &start);
}
