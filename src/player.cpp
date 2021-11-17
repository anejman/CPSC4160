/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "player.h"

Player::Player(SDL_Renderer *gameRenderer, int start_x, int start_y)
{
   game_renderer = gameRenderer;
   x_pos = start_x;
   y_pos = start_y;

   player_init();
}

Player::~Player()
{
   SDL_DestroyTexture(player_texture);
}

void Player::player_init()
{
   // Object Rect Dimensions and Location
   player_rect.x = x_pos;
   player_rect.y = y_pos;
   player_rect.w = PLAYER_WIDTH;
   player_rect.h = PLAYER_HEIGHT;

   imageHandler = new ImageHandler(game_renderer);
   player_texture = imageHandler->imageHandler_load(player_file);

   player_sprite = new SpriteHandler(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_FRAMES, PLAYER_SPRITE_DURATION);
}

void Player::player_update()
{
   unsigned current_frame_time = SDL_GetTicks();

   // Controls Sprite
   switch (motion_state)
   {
   case STATE_IDLE:
      current_frame = player_sprite->sprite_update(ANIMATION_REST);
      player_flip = (isFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
      break;
   case STATE_UP:
      current_frame = player_sprite->sprite_update(ANIMATION_STRUT);
      player_flip = (isFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
      break;
   case STATE_DOWN:
      current_frame = player_sprite->sprite_update(ANIMATION_STRUT);
      player_flip = (isFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
      break;
   case STATE_LEFT:
      current_frame = player_sprite->sprite_update(ANIMATION_STRUT);
      player_flip = SDL_FLIP_NONE;
      isFlipped = 0;
      break;
   case STATE_RIGHT:
      current_frame = player_sprite->sprite_update(ANIMATION_STRUT);
      player_flip = SDL_FLIP_HORIZONTAL;
      isFlipped = 1;
      break;
   case STATE_FEED:
      current_frame = player_sprite->sprite_update(ANIMATION_FEED);
      player_flip = (isFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
      break;
   default:
      current_frame = player_sprite->sprite_update(ANIMATION_REST);
      player_flip = SDL_FLIP_NONE;
   }

   // Move the player left or right
   player_set_x_pos(player_get_x_pos() + x_vel);

   // If the player went too far to the left or right move back
   if ((player_get_x_pos() < 0) || (player_get_x_pos() + PLAYER_WIDTH > level_width))
   {
      player_set_x_pos(player_get_x_pos() - x_vel);
   }

   // Move the player up or down
   player_set_y_pos(player_get_y_pos() + y_vel);

   // If the player went too far up or down move back
   if ((player_get_y_pos() < 0) || (player_get_y_pos() + PLAYER_HEIGHT > level_height))
   {
      player_set_y_pos(player_get_y_pos() - y_vel);
   }

   last_frame_time = current_frame_time;
}

void Player::player_render(SDL_Rect camera_rect)
{
   player_camera_x = (player_rect.x - camera_rect.x);
   player_camera_y = (player_rect.y - camera_rect.y);

   SDL_Rect render_rect = { player_camera_x, player_camera_y, PLAYER_WIDTH, PLAYER_HEIGHT};
   
   SDL_RenderCopyEx(game_renderer, player_texture, &current_frame, &render_rect, 0.0, NULL, player_flip);  
}