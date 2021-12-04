/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "camera.h"
#include "trident.h"
#include "globals.h"
#include "tileHandler.h"
#include "player.h"
#include "imageHandler.h"
#include "particleHandler.h"
#include "levelEditor.h"
#include "pauseMenu.h"
#include "score.h"
#include "startMenu.h"
#include "passiveAI.h"
#include "enemyAI.h"

using namespace std;

#define TRIDENT_PARTICLES 10
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
      std::vector<Trident *> tridents;
      vector<passiveAI *> NPCs;
      vector<enemyAI *> enemys;
      vector<Tile *> walls;
      TileHandler *tileHandler;
      Camera *camera;
      levelEditor *editor;
      particleHandler *bubbles;
      particleHandler *stars;
      particleHandler *bubbleBump;
      particleHandler *win;
      particleHandler *blood;
      SDL_Window *gameWindow;
      SDL_Renderer *gameRenderer;
      SDL_Event userInput;
      SDL_Rect camera_rect;
      SDL_Rect trident_rect;
      SDL_Rect NPCs_rect;
      SDL_Rect enemy_rect;
      StartMenu *startMenu;
      PauseMenu *pauseMenu;
      Score *score;
      int sprite_number;
      int game_state;
      int tile_type;
      int curr_layer;
      bool start;
      bool pause;
      bool restart;
};

#endif