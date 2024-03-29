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
#define PLAYER_WIDTH 58
#define PLAYER_HEIGHT 98

// Food Dimensions Definition
#define TRIDENT_WIDTH 64
#define TRIDENT_HEIGHT 64

// Max Number of Trident Objects
#define MAX_TRIDENTS 5

// Health Dimensions Definition
#define HEALTH_X 10
#define HEALTH_Y 10
#define HEALTH_WIDTH 64
#define HEALTH_HEIGHT 64

// Max Number of Lives
#define MAX_HEALTH 3

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
#define TILE_TYPE_NUM 16

//Number of backgroundlayers
#define LAYER_NUM 3

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

// Particle Variables
#define MAX_PARTICLE 10
#define MAX_PARTICLE_STAR 5
#define MAX_PARTICLE_WIN 50

// Particle Types
#define DEFAULT_TYPE 10
#define BUBBLE 0
#define STAR 1
#define BUBBLE_BUMP 2
#define WIN 3
#define BLOOD 4

// AI States
#define IDLE 0
#define WONDER 1
#define FLEE 2
#define ATTACK 3

// AI Size
#define AI_HEIGHT 64
#define AI_WIDTH 64
#define MAX_AI 6
#define MAX_ENEMY 3

// AI Travel Distance
#define FLEE_DIST 200
#define WONDER_DIST 50
#define ATTACK_DIST 200
#define ESCAPE_DIST 400

// Score position
#define SCORE_X 530
#define SCORE_Y 15

// Font colors
#define WHITE {255, 255, 255}
#define HOVER_COLOR {252, 204, 76}

#endif