/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <vector>
#include <random>
#include <string>

#ifndef GLOBALS_H
#define GLOBALS_H

// Screen Dimensions Definition
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Level Dimensions Definition
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960

// Player Dimensions Definition
#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64

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
#define STATE_FEED 5

// Player Animations
#define ANIMATION_STRUT 0
#define ANIMATION_FEED 1
#define ANIMATION_REST 2
#define ANIMATION_RUN 3

// Tile Dimensions
#define EDITOR_TILE_WIDTH 32
#define EDITOR_TILE_HEIGHT 32

// Number of different tile types
#define TILE_TYPE_NUM 9
#endif