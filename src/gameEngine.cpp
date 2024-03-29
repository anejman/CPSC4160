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

   if (TTF_Init() < 0)
   {
      cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
   }
   else
   {
      cout << "Finished TTF_Init!" << endl;
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

   //get wall cord
   walls = tileHandler->getWalls();

   // Initialize Health
   for (int i = 0; i < MAX_HEALTH; i++)
   {
      healths.push_back(new Health(gameRenderer, HEALTH_WIDTH * i));
   }
   total_health = 3;
   health_frame = 0;
   destroy_health = false;

   // Initialize Player
   player = new Player(gameRenderer, (SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2), PLAYER_Y);

   // Initialize Sprite Number
   sprite_number = 0;

   // Initialize Camera
   camera = new Camera();

   // Initialize Trident
   for (int i = 0; i < MAX_TRIDENTS; i++)
   {
      tridents.push_back(new Trident(gameRenderer, walls));
   }

   // Initialize AI
   for (int i = 0; i < MAX_AI; i++)
   {
      NPCs.push_back(new passiveAI(gameRenderer, walls));
   }

   // Initialize Enemy
   for (int i = 0; i < MAX_ENEMY; i++)
   {
      enemys.push_back(new enemyAI(gameRenderer, walls));
   }

   // Initialize particles
   bubbles = new particleHandler();
   stars = new particleHandler();
   bubbleBump = new particleHandler();
   win = new particleHandler();
   blood = new particleHandler();

   // Initialize game state
   game_state = 0;

   //Initialize level editor
   editor = new levelEditor(gameRenderer);

   // Initialize Start Menu
   startMenu = new StartMenu(gameRenderer);
   startMenu->init();
   start = false;

   // Initialize pause menu
   pauseMenu = new PauseMenu(gameRenderer);
   pauseMenu->init();
   pause = false;
   restart = false;

   // Initialize end menu
   endMenu = new EndMenu(gameRenderer);
   endMenu->init();
   winner = false;
   loser = false;

   // Initialize score
   score = new Score(gameRenderer);
   score->init();
}

void GameEngine::handleEvents()
{
   while (SDL_PollEvent(&this->userInput))
   {
      if (!start)
      {
         switch (userInput.type)
         {
         case SDL_MOUSEMOTION:
            if (userInput.motion.x > MENU_ITEM_X && userInput.motion.x < MENU_ITEM_X + 200)
            {
               if (userInput.motion.y > START_Y && userInput.motion.y < START_Y + 50)
               {
                  startMenu->hoverEffect(1);
               }
               else if (userInput.motion.y > SWAPPER_Y && userInput.motion.y < SWAPPER_Y + 50)
               {
                  startMenu->hoverEffect(2);
               }
               else
               {
                  startMenu->hoverEffect(0);
               }
            }
            else
            {
               startMenu->hoverEffect(0);
            }
            break;

         case SDL_MOUSEBUTTONDOWN:
            if (userInput.button.x > MENU_ITEM_X && userInput.button.x < MENU_ITEM_X + 200)
            {
               if (userInput.button.y > START_Y && userInput.button.y < START_Y + 50)
               {
                  start = true;
                  delete startMenu;
                  std::cout << "Start" << std::endl;
               }
               else if (userInput.button.y > SWAPPER_Y && userInput.button.y < SWAPPER_Y + 50)
               {
                  sprite_number++;

                  if (sprite_number > 3)
                  {
                     sprite_number = 0;
                  }

                  player->player_set_sprite(sprite_number);

                  std::cout << "Change Character" << std::endl;
               }
            }
            break;
         case SDL_QUIT:
            runGame = false;
            break;
         default:
            break;
         }
      }
      else if (!pause)
      {
         if (winner || loser)
         {
            switch (userInput.type)
            {
            case SDL_MOUSEMOTION:
               if (userInput.motion.x > MENU_ITEM_X && userInput.motion.x < MENU_ITEM_X + 200)
               {
                  if (userInput.motion.y > RESTART_Y + 60 && userInput.motion.y < RESTART_Y + 110)
                  {
                     endMenu->hoverEffect(1);
                  }
                  else if (userInput.motion.y > QUIT_Y + 60 && userInput.motion.y < QUIT_Y + 110)
                  {
                     endMenu->hoverEffect(2);
                  }
                  else
                  {
                     endMenu->hoverEffect(0);
                  }
               }
               else
               {
                  endMenu->hoverEffect(0);
               }
               break;

            case SDL_MOUSEBUTTONDOWN:
               if (userInput.button.x > MENU_ITEM_X && userInput.button.x < MENU_ITEM_X + 200)
               {
                  if (userInput.button.y > RESTART_Y + 60 && userInput.button.y < RESTART_Y + 110)
                  {
                     restart = true;
                     cout << "Restart" << endl;
                  }
                  else if (userInput.button.y > QUIT_Y + 60 && userInput.button.y < QUIT_Y + 110)
                  {
                     runGame = false;
                     cout << "Quit" << endl;
                  }
               }
               break;
            case SDL_QUIT:
               runGame = false;
               break;
            default:
               break;
            }
         }
         else
         {
            switch (userInput.type)
            {
            case SDL_QUIT:
               runGame = false;
            case SDL_KEYDOWN:
               switch (userInput.key.keysym.sym)
               {
               case SDLK_UP:
                  if (game_state == STATE_PLAYER)
                  {
                     player->player_set_y_vel(-Y_VEL);
                     player->player_set_state(STATE_UP);
                  }
                  else
                  {
                     if (editor->editor_get_y_pos() > 0)
                     {
                        editor->editor_set_y_pos(editor->editor_get_y_pos() - EDITOR_TILE_HEIGHT);
                     }
                  }
                  break;
               case SDLK_DOWN:
                  if (game_state == STATE_PLAYER)
                  {
                     player->player_set_y_vel(Y_VEL);
                     player->player_set_state(STATE_DOWN);
                  }
                  else
                  {
                     if (editor->editor_get_y_pos() + EDITOR_TILE_HEIGHT < LEVEL_HEIGHT)
                     {
                        editor->editor_set_y_pos(editor->editor_get_y_pos() + EDITOR_TILE_HEIGHT);
                     }
                  }
                  break;
               case SDLK_LEFT:
                  if (game_state == STATE_PLAYER)
                  {
                     player->player_set_x_vel(-X_VEL);
                     player->player_set_state(STATE_LEFT);
                  }
                  else
                  {
                     if (editor->editor_get_x_pos() > 0)
                     {
                        editor->editor_set_x_pos(editor->editor_get_x_pos() - EDITOR_TILE_WIDTH);
                     }
                  }
                  break;
               case SDLK_RIGHT:
                  if (game_state == STATE_PLAYER)
                  {
                     player->player_set_x_vel(X_VEL);
                     player->player_set_state(STATE_RIGHT);
                  }
                  else
                  {
                     if (editor->editor_get_x_pos() + EDITOR_TILE_WIDTH < LEVEL_WIDTH)
                     {
                        editor->editor_set_x_pos(editor->editor_get_x_pos() + EDITOR_TILE_WIDTH);
                     }
                  }
                  break;
               case SDLK_SPACE:
                  if (game_state != STATE_PLAYER)
                  {
                     std::cout << "Tile Type:" << tile_type << std::endl;
                     std::cout << "Layer:" << curr_layer << std::endl;
                     editor->editor_update(tile_type, curr_layer);
                     tileHandler->tileHandler_clean();
                     tileHandler->tileHandler_load();
                  }
                  break;
               case SDLK_p:
                  game_state = (game_state + 1) % 2;
                  curr_layer = 0;
                  editor->editor_init(0, 0);
                  if (game_state == STATE_PLAYER)
                  {
                     SDL_SetWindowTitle(gameWindow, "Collection Game");
                  }
                  else
                  {
                     SDL_SetWindowTitle(gameWindow, "Now Editing Game...");
                     tile_type = 0;
                  }
                  break;
               case SDLK_w:
                  if (game_state == STATE_EDITOR)
                  {
                     curr_layer = (curr_layer + 1) % LAYER_NUM;
                  }
                  break;
               case SDLK_a:
                  if (game_state == STATE_EDITOR)
                  {
                     tile_type = ((tile_type - 1) % TILE_TYPE_NUM + TILE_TYPE_NUM) % TILE_TYPE_NUM;
                  }
                  break;
               case SDLK_s:
                  if (game_state == STATE_EDITOR)
                  {
                     tile_type = 0;
                  }
                  break;
               case SDLK_d:
                  if (game_state == STATE_EDITOR)
                  {
                     tile_type = (tile_type + 1) % TILE_TYPE_NUM;
                  }
                  break;
               case SDLK_ESCAPE:
                  pause = true;
                  break;
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
                  break;
               case SDLK_RIGHT:
               case SDLK_LEFT:
                  player->player_set_x_vel(0);
                  break;
               }
               break;
            }
         }
      }
      else
      {
         switch (userInput.type)
         {
         case SDL_MOUSEMOTION:
            if (userInput.motion.x > MENU_ITEM_X && userInput.motion.x < MENU_ITEM_X + 200)
            {
               if (userInput.motion.y > RESUME_Y && userInput.motion.y < RESUME_Y + 50)
               {
                  pauseMenu->hoverEffect(1);
               }
               else if (userInput.motion.y > RESTART_Y && userInput.motion.y < RESTART_Y + 50)
               {
                  pauseMenu->hoverEffect(2);
               }
               else if (userInput.motion.y > QUIT_Y && userInput.motion.y < QUIT_Y + 50)
               {
                  pauseMenu->hoverEffect(3);
               }
               else
               {
                  pauseMenu->hoverEffect(0);
               }
            }
            else
            {
               pauseMenu->hoverEffect(0);
            }
            break;

         case SDL_MOUSEBUTTONDOWN:
            if (userInput.button.x > MENU_ITEM_X && userInput.button.x < MENU_ITEM_X + 200)
            {
               if (userInput.button.y > RESUME_Y && userInput.button.y < RESUME_Y + 50)
               {
                  pause = false;
                  cout << "Resume" << endl;
               }
               else if (userInput.button.y > RESTART_Y && userInput.button.y < RESTART_Y + 50)
               {
                  restart = true;
                  cout << "Restart" << endl;
               }
               else if (userInput.button.y > QUIT_Y && userInput.button.y < QUIT_Y + 50)
               {
                  runGame = false;
                  cout << "Quit" << endl;
               }
            }
            break;
         case SDL_KEYDOWN:
            switch (userInput.key.keysym.sym)
            {
            case SDLK_ESCAPE:
               pause = false;
               cout << "Resume w/ ESC key" << endl;
               break;
            default:
               break;
            }
            break;
         case SDL_QUIT:
            runGame = false;
            break;
         default:
            break;
         }
      }
   }
}

void GameEngine::updateMechanics()
{
   if (!start)
   {
      player->player_update();
   }
   else if (game_state == STATE_PLAYER && !pause && !(winner || loser))
   {
      player->player_update();
      camera->camera_update(player->player_get_x_pos(), player->player_get_y_pos());

      if (destroy_health)
      {
         if (health_frame > 3)
         {
            destroy_health = false;
            total_health--;
            health_frame = 0;
         }
         else
         {
            health_frame++;
            healths[total_health - 1]->health_update(health_frame);

            if (total_health - 1 == 0)
            {
               loser = true;
               cout << "Loser :(" << endl;
            }
         }
      }

      for (auto trident_it = begin(tridents); trident_it != end(tridents);)
      {
         trident_rect = (*trident_it)->trident_get_rect();
         camera_rect = camera->camera_get_rect();

         if (checkCollision(player->player_get_rect(), trident_rect) && player->player_get_state())
         {
            trident_it = tridents.erase(trident_it);
            if (score->increment())
            {
               winner = true;
               endMenu->setState(1);
               cout << "Winner!" << endl;

               win->phInit("./assets/star.png", gameRenderer, 0, 0, 25, 25, WIN);
            }
            // Initialize Particles
            int tempX = trident_rect.x - camera_rect.x;
            int tempY = trident_rect.y - camera_rect.y;
            stars->phInit("./assets/star.png", gameRenderer, tempX, tempY, 25, 25, STAR);
         }
         else
         {
            ++trident_it;
         }
      }

      //loops through every NPC
      for (auto ai_it = begin(NPCs); ai_it != end(NPCs);)
      {
         (*ai_it)->aiUpdate(player->player_get_rect());

         NPCs_rect = (*ai_it)->getRect();

         //randomly display a bubble effect with NPCs
         if (((rand() + 1) % 1000) == 0)
         {
            int tempX = NPCs_rect.x - camera_rect.x;
            int tempY = NPCs_rect.y - camera_rect.y;
            bubbles->phInit("./assets/BUBBLES.png", gameRenderer, tempX, tempY, 10, 10, BUBBLE);
         }

         //checks for collision with player
         //if collision detected, set NPC to flee state
         if (checkCollision(player->player_get_rect(), NPCs_rect))
         {
            (*ai_it)->setState(FLEE);

            //makes NPC flee opposite of player position
            if (player->player_get_x_pos() > (*ai_it)->getRect().x)
            {
               (*ai_it)->setXVel(-10);
            }
            else
            {
               (*ai_it)->setXVel(10);
            }
            (*ai_it)->setYVel(5 - (rand() % 11));

            //initialize a bubble bump effect
            int tempX = NPCs_rect.x - camera_rect.x;
            int tempY = NPCs_rect.y - camera_rect.y;
            bubbleBump->phInit("./assets/BUBBLES.png", gameRenderer, tempX, tempY, 10, 10, BUBBLE_BUMP);
         }

         ++ai_it;
      }

      //store collision vel of shark
      int collisionXVel = 0;
      int collisionYVel = 0;

      //loops through all sharks
      for (auto ai_it = begin(enemys); ai_it != end(enemys);)
      {
         enemy_rect = (*ai_it)->getRect();

         //sets shark to attack state when player position is within a certain distance of shark
         int attCondX = abs(((*ai_it)->getXPos() - camera_rect.x) - (player->player_get_x_pos() - camera_rect.x));
         int attCondY = abs(((*ai_it)->getYPos() - camera_rect.y) - (player->player_get_y_pos() - camera_rect.y));
         if (attCondX < ATTACK_DIST && attCondY < ATTACK_DIST && !(*ai_it)->getReturning())
         {
            (*ai_it)->setState(ATTACK);

            //makes shark swim towards player position
            if (player->player_get_x_pos() > (*ai_it)->getXPos())
            {
               (*ai_it)->setXVel(2);
            }
            else
            {
               (*ai_it)->setXVel(-2);
            }

            if (player->player_get_y_pos() > (*ai_it)->getYPos())
            {
               (*ai_it)->setYVel(2);
            }
            else
            {
               (*ai_it)->setYVel(-2);
            }
         }

         //on collision, switch shark back to idle state
         //makes shark return to it's original position
         if (checkCollision(player->player_get_rect(), enemy_rect) && !(*ai_it)->getReturning())
         {
            (*ai_it)->setState(IDLE);

            (*ai_it)->setReturning(1);

            //rebound player on collision by shark
            player->player_set_x_pos(player->player_get_x_pos() + 5 * (*ai_it)->getXVel());
            player->player_set_y_pos(player->player_get_y_pos() + 5 * (*ai_it)->getYVel());
            collisionXVel = 5 * (*ai_it)->getXVel();
            collisionYVel = 5 * (*ai_it)->getYVel();

            //rebound player when player hits shark
            player->player_set_x_pos(player->player_get_x_pos() - 5 * player->player_get_x_vel());
            player->player_set_y_pos(player->player_get_y_pos() - 5 * player->player_get_y_vel());

            //stun player
            player->player_set_x_vel(0);
            player->player_set_y_vel(0);

            //initialize blood effect
            int tempX = ((player->player_get_x_pos() + enemy_rect.x) / 2 - camera_rect.x);
            int tempY = ((player->player_get_y_pos() + enemy_rect.y) / 2 - camera_rect.y);
            blood->phInit("./assets/blood.png", gameRenderer, tempX, tempY, 25, 25, BLOOD);

            destroy_health = true;
         }

         (*ai_it)->aiUpdate(player->player_get_rect());

         ++ai_it;
      }

      //loops through every wall position
      for (int x = 0; x < (int)walls.size(); x++)
      {
         //on collision stops player from moving
         if (checkCollision(player->player_get_rect(), walls[x]->getRect()))
         {
            //if player is knocked into wall by shark with 0 vel, makes sure player does not move past wall
            if (player->player_get_x_vel() == 0 && player->player_get_y_vel() == 0)
            {
               player->player_set_x_pos(player->player_get_x_pos() - collisionXVel);
               player->player_set_y_pos(player->player_get_y_pos() - collisionYVel);
            }
            else
            {
               player->player_set_x_pos(player->player_get_x_pos() - player->player_get_x_vel());
               player->player_set_y_pos(player->player_get_y_pos() - player->player_get_y_vel());
            }
         }
      }

      blood->phUpdate();
      bubbleBump->phUpdate();
      bubbles->phUpdate();
      stars->phUpdate();
   }
   else
   {
      camera->camera_update(editor->editor_get_x_pos(), editor->editor_get_y_pos());
   }

   //updates win effect when player wins
   if (winner)
   {
      win->phUpdate();
   }
}

void GameEngine::render()
{
   SDL_RenderClear(gameRenderer);

   if (!start)
   {
      startMenu->render();
      camera_rect = camera->camera_get_rect();
      player->player_render(camera_rect);
   }
   else if (!pause)
   {
      if (winner || loser)
      {
         endMenu->render();

         //render win effect when players win
         if (winner)
         {
            win->phRender(gameRenderer);
         }
      }
      else
      {
         camera_rect = camera->camera_get_rect();
         tileHandler->tileHandler_render(camera_rect, 0);
         tileHandler->tileHandler_render(camera_rect, 1);

         if (game_state == STATE_PLAYER)
         {
            for (Trident *trident : tridents)
            {
               trident->trident_render(camera_rect);
            }

            //render NPCs
            for (passiveAI *AI : NPCs)
            {
               AI->aiRender(camera_rect);
            }

            //render Enemies
            for (enemyAI *enemy : enemys)
            {
               enemy->aiRender(camera_rect);
            }

            player->player_render(camera_rect);

            tileHandler->tileHandler_render(camera_rect, 2);

            score->render();

            stars->phRender(gameRenderer);
            bubbles->phRender(gameRenderer);
            bubbleBump->phRender(gameRenderer);
            blood->phRender(gameRenderer);

            for (Health *health : healths)
            {
               health->health_render();
            }
         }
         else
         {
            if (curr_layer > 1)
               tileHandler->tileHandler_render(camera_rect, 2);
            editor->editor_render(camera_rect);
         }
      }
   }
   else
   {
      pauseMenu->render();
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
   first_rect_right = first_rect.x + first_rect.w / 2;

   second_rect_top = second_rect.y;
   second_rect_bottom = second_rect.y + second_rect.h;
   second_rect_left = second_rect.x;
   second_rect_right = second_rect.x + second_rect.w / 2;

   if (first_rect_top > second_rect_bottom)
      return false;
   if (first_rect_bottom < second_rect_top)
      return false;
   if (first_rect_left > second_rect_right)
      return false;
   if (first_rect_right < second_rect_left)
      return false;

   return true;
}

void GameEngine::reinit()
{
   // Free elements
   cout << "Deleting" << endl;
   delete player;
   delete camera;

   healths.clear();
   tridents.clear();
   NPCs.clear();
   enemys.clear();

   // Initialize Player
   player = new Player(gameRenderer, (SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2), PLAYER_Y);
   player->player_set_sprite(sprite_number);

   // Initialize Camera
   camera = new Camera();

   // Initialize Health
   for (int i = 0; i < MAX_HEALTH; i++)
   {
      healths.push_back(new Health(gameRenderer, HEALTH_WIDTH * i));
   }
   total_health = 3;
   health_frame = 0;
   destroy_health = false;

   // Initialize Trident
   for (int i = 0; i < MAX_TRIDENTS; i++)
   {
      tridents.push_back(new Trident(gameRenderer, walls));
   }

   // Initialize AI
   for (int i = 0; i < MAX_AI; i++)
   {
      NPCs.push_back(new passiveAI(gameRenderer, walls));
   }

   // Initialize Enemy
   for (int i = 0; i < MAX_ENEMY; i++)
   {
      enemys.push_back(new enemyAI(gameRenderer, walls));
   }

   // Initialize game state
   game_state = 0;

   pause = false;
   restart = false;
   winner = false;
   loser = false;

   endMenu->setState(0);

   score->resetScore();
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