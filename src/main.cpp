/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "globals.h"
#include "gameEngine.h"

int main()
{
    GameEngine *gameEngine = new GameEngine();

    gameEngine->init();

    // FPS Controller
    Uint32 this_start_time;
    Uint32 last_count_start_time;
    int this_duration;
    int fps_counter;

    // Game Loop
    while (gameEngine->runGame)
    {
        this_start_time = SDL_GetTicks();

        gameEngine->handleEvents();
        gameEngine->updateMechanics();
        gameEngine->render();

        fps_counter++;

        if (this_start_time >= (last_count_start_time + 1000))
        {
            last_count_start_time = this_start_time;
            fps_counter = 0;
        }

        this_duration = SDL_GetTicks() - this_start_time;

        if (this_duration < FRAME_DURATION)
        {
            SDL_Delay(FRAME_DURATION - this_duration);
        }

        if (gameEngine->getRestart())
        {
            gameEngine->reinit();
        }
    }

    gameEngine->quit();

    delete gameEngine;

    return 0;
}