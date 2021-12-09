#include "passiveAI.h"

//collision check helper func
bool checkCollisionP(SDL_Rect first_rect, SDL_Rect second_rect)
{
   int first_rect_top, first_rect_bottom, first_rect_left, first_rect_right;
   int second_rect_top, second_rect_bottom, second_rect_left, second_rect_right;

   first_rect_top = first_rect.y;
   first_rect_bottom = first_rect.y + first_rect.h;
   first_rect_left = first_rect.x;
   first_rect_right = first_rect.x + first_rect.w/2;

   second_rect_top = second_rect.y;
   second_rect_bottom = second_rect.y + second_rect.h;
   second_rect_left = second_rect.x;
   second_rect_right = second_rect.x + second_rect.w/2;

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

passiveAI::passiveAI(SDL_Renderer *ren, std::vector<Tile *> wallPos) 
{
    aiRenderer = ren;

    //store wall positions
    walls = wallPos;

    aiInit();
}

passiveAI::~passiveAI() {}

void passiveAI::aiInit()
{
    imageHandler = new ImageHandler(aiRenderer);
    
    //randomizes ai sprite with according sizes
    switch (rand() % 4)
    {
        case 0:
            aiTexture = imageHandler->imageHandler_load(lightfish_file);

            ai_sprite = new SpriteHandler(LIGHT_SPRITE_WIDTH, LIGHT_SPRITE_HEIGHT, LIGHT_SPRITE_FRAMES, AI_SPRITE_DURATION);

            aiHeight = AI_HEIGHT - AI_HEIGHT/4;
            aiWidth = AI_WIDTH;
            break;

        case 1:
            aiTexture = imageHandler->imageHandler_load(turtle_file);

            ai_sprite = new SpriteHandler(TURTLE_SPRITE_WIDTH, TURTLE_SPRITE_HEIGHT, TURTLE_SPRITE_FRAMES, AI_SPRITE_DURATION);

            aiHeight = AI_HEIGHT;
            aiWidth = AI_WIDTH + AI_WIDTH/4;
            break;

        case 2:
            aiTexture = imageHandler->imageHandler_load(whale_file);

            ai_sprite = new SpriteHandler(WHALE_SPRITE_WIDTH, WHALE_SPRITE_HEIGHT, WHALE_SPRITE_FRAMES, AI_SPRITE_DURATION);

            aiHeight = AI_HEIGHT*2;
            aiWidth = AI_WIDTH*2 + AI_WIDTH/4;
            break;

        case 3:
            aiTexture = imageHandler->imageHandler_load(clownfish_file);

            ai_sprite = new SpriteHandler(CLOWN_SPRITE_WIDTH, CLOWN_SPRITE_HEIGHT, CLOWN_SPRITE_FRAMES, AI_SPRITE_DURATION);

            aiHeight = AI_HEIGHT/2;
            aiWidth = AI_WIDTH/2 + AI_WIDTH/4;
            break;
    }

    flipAI = SDL_FLIP_NONE;

    std::random_device rd;
    std::mt19937 mt(rd());

    int validCord = false;

    //loops until a valid spawn position
    while (!validCord)
    {
        std::uniform_real_distribution<double> widthDist(0, LEVEL_WIDTH - aiWidth);
        std::uniform_real_distribution<double> heightDist(0, LEVEL_HEIGHT - aiHeight);

        xPos = (int)widthDist(mt);
        yPos = (int)heightDist(mt);

        SDL_Rect temp = {xPos, yPos, aiWidth, aiHeight};

        validCord = true;

        //checks to make sure spawn position is not a wall
        for (int x = 0; x < (int)walls.size(); x++)
        {
            if (checkCollisionP(temp, walls[x]->getRect()))
            {
                validCord = false;
            }
        }
    }
    
    aiRect.w = aiWidth;
    aiRect.h = aiHeight;

    xVel = 0;
    yVel = 0;

    state = IDLE;
    wonderPos = 0;
}

void passiveAI::aiUpdate(SDL_Rect player) 
{
    //FSM
    switch (state)
    {
    case IDLE:
        xVel = 0;
        yVel = 0;

        currentFrame = ai_sprite->sprite_update(IDLE);

        //randomly switches to wonder state
        if ((rand() % 50) == 0)
        {
            state = WONDER;
            wonderPos = xPos;

            xVel = 3 - (rand() % 7);
            yVel = 3 - (rand() % 7);
        }
        break;
    
    case WONDER:
        currentFrame = ai_sprite->sprite_update(WONDER);

        //wonders until a certain distance is hit, switches to idle
        if (abs(xPos - wonderPos) > WONDER_DIST)
        {
            state = IDLE;
        }

        //if randomized xVel is zero, switch to idle
        //prevents infinite wonder
        if (xVel == 0)
        {
            state = IDLE;
        }
        break;

    case FLEE:
        currentFrame = ai_sprite->sprite_update(WONDER);

        //flees until a certain distance is hit, switches to idle 
        if (abs(player.x - xPos) > FLEE_DIST) 
        {
            state = IDLE;
        }

        //if randomized xVel is zero, switch to idle
        if (xVel == 0)
        {
            state = IDLE;
        }
        break;
    }

    //makes sure ai stays inbounds
    if (xPos > LEVEL_WIDTH) { xVel *= -2; }
    if (xPos < 0) { xVel *= -2; }
    if (yPos > LEVEL_HEIGHT) { yVel *= -2; }
    if (yPos < 0) { yVel *= -2; }

    bool collision = false;

    //checks for collisions with walls
    for (int x = 0; x < (int)walls.size(); x++)
    {
        if (checkCollisionP(aiRect, walls[x]->getRect())) 
        { 
            collision = true;
        }
    }

    //on collision bounces player back and switch to idle
    if (collision)
    {
        xVel *= -2;
        yVel *= -2;
        state = IDLE; 
        collision = false;
    }

    //makes sprite face the correct direction
    if (xVel < 0) {
        flipAI = SDL_FLIP_HORIZONTAL;
    } 
    else 
    {
        flipAI = SDL_FLIP_NONE;
    }

    xPos += xVel;
    yPos += yVel;

    aiRect.x = xPos;
    aiRect.y = yPos;
}

void passiveAI::aiRender(SDL_Rect camera) 
{
    SDL_Rect renderRect = {(aiRect.x - camera.x), (aiRect.y - camera.y), aiRect.w, aiRect.h};
    SDL_RenderCopyEx(aiRenderer, aiTexture, &currentFrame, &renderRect, 0.0, NULL, flipAI);
}

void passiveAI::setState(int newState) 
{
    state = newState;
}

void passiveAI::setXVel(int vel)
{
    xVel = vel;
}

void passiveAI::setYVel(int vel)
{
    yVel = vel;
}