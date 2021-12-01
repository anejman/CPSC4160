/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <vector>
#include <random>
#include <string>

using namespace std;

#ifndef GLOBALS_H
#define GLOBALS_H

// Screen Dimensions Definition
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Level Dimensions Definition
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960

// Player Dimensions Definition
#define PLAYER_WIDTH 78
#define PLAYER_HEIGHT 138

// Food Dimensions Definition
#define FOOD_WIDTH 64
#define FOOD_HEIGHT 64

// Max Number of Food Objects
#define MAX_FOOD 10

// Frames Per Second Definition
#define FPS 60
#define FRAME_DURATION 1000 / FPS

// Velocity Definition
#define X_VEL 5
#define Y_VEL 5

// Player States
#define STATE_IDLE 0
#define STATE_UP 1
#define STATE_DOWN 2
#define STATE_LEFT 3
#define STATE_RIGHT 4

// Player Animations
#define ANIMATION_DOWN 0
#define ANIMATION_LEFT 1
#define ANIMATION_RIGHT 2
#define ANIMATION_UP 3

// Tile Dimensions
#define EDITOR_TILE_WIDTH 32
#define EDITOR_TILE_HEIGHT 32

// Number of different tile types
#define TILE_TYPE_NUM 9

// Start Menu Positions
#define TITLE_Y 30
#define PLAYER_Y 160
#define SWAPPER_Y 300
#define START_Y 400

// Pause Menu Positions
#define MENU_ITEM_X 220
#define RESUME_Y 110
#define RESTART_Y 190
#define QUIT_Y 270

// Particle variables
#define MAX_PARTICLE 10
#define MAX_PARTICLE_STAR 5
#define DEFAULT_TYPE 10
#define BUBBLE 0
#define STAR 1
#define BUBBLE_BUMP 2

// Score position
#define SCORE_X 530
#define SCORE_Y 15

#endif