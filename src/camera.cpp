/******************************
 * Alex Nejman
 * CPSC 4160 Fall 2021
 * Username: anejman
 * Instructor: Victor Zordan
 ******************************/

#include "camera.h"

Camera::Camera()
{
	camera_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

Camera::~Camera() {}

void Camera::camera_update(int player_x_pos, int player_y_pos)
{
	// Center camera on player
	camera_rect.x = (player_x_pos + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera_rect.y = (player_y_pos + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	// Keep camera in bounds
	if (camera_rect.x < 0)
	{
		camera_rect.x = 0;
	}

	if (camera_rect.y < 0)
	{
		camera_rect.y = 0;
	}

	if (camera_rect.x > level_width - camera_rect.w)
	{
		camera_rect.x = level_width - camera_rect.w;
	}

	if (camera_rect.y > level_height - camera_rect.h)
	{
		camera_rect.y = level_height - camera_rect.h;
	}
}