/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "camera.h"
#include "food.h"
#include "globals.h"
#include "tileHandler.h"
#include "player.h"
#include "imageHandler.h"
#include "particleHandler.h"
#include "levelEditor.h"
#include "menu.h"
#include "score.h"

using namespace std;

#define FOOD_PARTICLES 10
#define STATE_PLAYER 0
#define STATE_EDITOR 1

class GameEngine
{
   public:
      GameEngine();
      ~GameEngine();

      void init();
      void handleEvents();
      void updateMechanics();
      void render();
      bool checkCollision(SDL_Rect first_rect, SDL_Rect second_rect);
      void reinit();
      void quit();
      bool getRestart() { return restart; }

      bool runGame = true;

   private:
      Player *player;
      std::vector<Food *> foods;
      TileHandler *tileHandler;
      Camera *camera;
      levelEditor *editor;
      particleHandler* Bubbles;
      SDL_Window *gameWindow;
      SDL_Renderer *gameRenderer;
      SDL_Event userInput;
      SDL_Rect camera_rect;
      SDL_Rect food_rect;
      GameMenu *menu;
      Score *score;
      int game_state;
      int tile_type;
      bool pause;
      bool restart;
};

#endif