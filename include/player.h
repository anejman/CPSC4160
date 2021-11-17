/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include "imageHandler.h"
#include "spriteHandler.h"

#define PLAYER_SPRITE_WIDTH 32
#define PLAYER_SPRITE_HEIGHT 32
#define PLAYER_SPRITE_FRAMES 4
#define PLAYER_SPRITE_DURATION 100

class Player
{
   public:
      Player(SDL_Renderer *gameRenderer, int x_pos, int y_pos);
      ~Player();

      void player_init();
      void player_update();
      void player_render(SDL_Rect camera_rect);

      // Getters
      int player_get_x_pos() { return player_rect.x; };
      int player_get_y_pos() { return player_rect.y; };
      int player_get_state() { return motion_state; };
      SDL_Rect player_get_rect() { return player_rect; };

      // Setters
      void player_set_x_pos(int pos) { player_rect.x = pos; };
      void player_set_y_pos(int pos) { player_rect.y = pos; };
      void player_set_x_vel(double vel) { x_vel = vel; };
      void player_set_y_vel(double vel) { y_vel = vel; };
      void player_set_state(unsigned state) { motion_state = state; }

   private:
      ImageHandler *imageHandler;
      SpriteHandler *player_sprite;
      SDL_Renderer *game_renderer;
      SDL_Texture *player_texture;
      SDL_Rect player_rect;
      SDL_Rect current_frame;
      SDL_RendererFlip player_flip;
      const char *player_file = "./assets/chicken.png";
      unsigned last_frame_time;
      unsigned motion_state;
      bool isFlipped = 0;
      int x_pos;
      int y_pos;
      double x_vel = 0;
      double y_vel = 0;
      int player_camera_x;
      int player_camera_y;
      int level_width = LEVEL_WIDTH;
      int level_height = LEVEL_HEIGHT;
};

#endif
