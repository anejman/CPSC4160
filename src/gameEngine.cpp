/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "gameEngine.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

void GameEngine::init()
{
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
   {
      std::cout << "Error Initializing SDL: " << SDL_GetError() << std::endl;
   }
   else
   {
      std::cout << "Finished SDL_INIT!" << std::endl;
   }

   // Enable GPU Textures
   IMG_Init(IMG_INIT_PNG);

   // Initialize Game Window
   gameWindow = SDL_CreateWindow("Collection Game",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 0);

   // Initialize Game Renderer
   gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);

   if (!gameRenderer)
   {
      std::cerr << "Error Initializing Game Renderer!" << std::endl;
   }

   // load Tile Map
   tileHandler = new TileHandler(gameRenderer);
   tileHandler->tileHandler_load();

   // Initialize Player
   player = new Player(gameRenderer, 0, 0);

   // Initialize Camera
   camera = new Camera();

   imageHandler = new ImageHandler(gameRenderer);
   particle_texture = imageHandler->imageHandler_load(particle_file); // NEW
   
   // Initialize Food
   for (int i = 0; i < MAX_FOOD; i++)
   {
      foods.push_back(new Food(gameRenderer));
   }
}

void GameEngine::handleEvents()
{
   while (SDL_PollEvent(&this->userInput))
   {
      switch (userInput.type)
      {
      case SDL_QUIT:
         runGame = false;
      case SDL_KEYDOWN:
         switch (userInput.key.keysym.sym)
         {
         case SDLK_UP:
            player->player_set_y_vel(-Y_VEL);
            player->player_set_state(STATE_UP);
            break;
         case SDLK_DOWN:
            player->player_set_y_vel(Y_VEL);
            player->player_set_state(STATE_DOWN);
            break;
         case SDLK_LEFT:
            player->player_set_x_vel(-X_VEL);
            player->player_set_state(STATE_LEFT);
            break;
         case SDLK_RIGHT:
            player->player_set_x_vel(X_VEL);
            player->player_set_state(STATE_RIGHT);
            break;
         case SDLK_SPACE:
            player->player_set_y_vel(0);
            player->player_set_state(STATE_FEED);
         default:
            break;
         }
         break;

      case SDL_KEYUP:
         switch (userInput.key.keysym.sym)
         {
         case SDLK_UP:
         case SDLK_DOWN:
            player->player_set_y_vel(0);
            player->player_set_state(STATE_IDLE);
            break;
         case SDLK_RIGHT:
         case SDLK_LEFT:
            player->player_set_x_vel(0);
            player->player_set_state(STATE_IDLE);
            break;
         case SDLK_SPACE:
            player->player_set_x_vel(0);
            player->player_set_state(STATE_IDLE);
            break;
         }
         break;
      }
   }
}

void GameEngine::updateMechanics()
{
   player->player_update();
   camera->camera_update(player->player_get_x_pos(), player->player_get_y_pos());
   
   for(auto food_it = begin(foods); food_it != end(foods);)
   {
      food_rect = (*food_it)->food_get_rect();
      camera_rect = camera->camera_get_rect();

      if(checkCollision(player->player_get_rect(), food_rect) && player->player_get_state() == STATE_FEED)
      {  
         food_it = foods.erase(food_it);

         // Initialize Particles
         for (int i = 0; i < FOOD_PARTICLES; i++)
         {
            particles.push_back(new ParticleHandler(gameRenderer, particle_texture, 8, 8, 160, 5));
         }

         particle_iteration = 0;
      }
      else
      {
         ++food_it;
      }
   }  
}

void GameEngine::render()
{
   SDL_RenderClear(gameRenderer);
   camera_rect = camera->camera_get_rect();
   tileHandler->tileHandler_render(camera_rect);

   for (Food *food : foods)
   {
      food->food_render(camera_rect);
   }

   player->player_render(camera_rect);

   for(auto particle_it = begin(particles); particle_it != end(particles);)
   {
      if((*particle_it)->isDead())
      {
         particle_it = particles.erase(particle_it);

         if(particle_iteration < FOOD_PARTICLES * 5)
         {
            particles.push_back(new ParticleHandler(gameRenderer, particle_texture, 8, 8, 160, 5));
            particle_iteration++;
         }
      }
      else
      {
         (*particle_it)->particleHandler_render(player->player_get_x_pos() - camera_rect.x, player->player_get_y_pos() - camera_rect.y);
         ++particle_it;
      }
   }

   SDL_RenderPresent(gameRenderer);
}

bool GameEngine::checkCollision(SDL_Rect first_rect, SDL_Rect second_rect)
{
   int first_rect_top, first_rect_bottom, first_rect_left, first_rect_right;
   int second_rect_top, second_rect_bottom, second_rect_left, second_rect_right;

   first_rect_top = first_rect.y;
   first_rect_bottom = first_rect.y + first_rect.h;
   first_rect_left = first_rect.x;
   first_rect_right = first_rect.x + first_rect.w;

   second_rect_left = second_rect.y;
   second_rect_right = second_rect.y + second_rect.h;
   second_rect_top = second_rect.x;
   second_rect_bottom = second_rect.x + second_rect.w;

   if (first_rect_top > second_rect_right) return false;
   if (first_rect_bottom < second_rect_left) return false;
   if (first_rect_left > second_rect_bottom) return false;
   if (first_rect_right < second_rect_top) return false;
   
   return true;
}

void GameEngine::quit()
{
   // Destroys SDL Objects
   SDL_DestroyRenderer(gameRenderer);
   SDL_DestroyWindow(gameWindow);

   // Quits Program
   IMG_Quit();
   SDL_Quit();
}