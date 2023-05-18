#pragma once

//	TILES DEFINITION
#define WATER 0
#define DIRT 1
#define WORM 2
#define DIG 3
#define ROCK 4
#define GRASS 5
#define WALL 6
#define NEANT 7
#define TILES_PATH "assets/tiles_sheet.png"
#define TILES_H 32
#define TILES_W 32
#define TEX_BY_ROW 10

//CHARACTERS DEFINITION
#define PLAYER_PATH "assets/rat_taupe_sheet.png"
#define PLAYER_TEX_SIZE 100
#define PLAYER_ANIM_SPEED 200
#define PLAYER_IDLE_FRAMES 1
#define PLAYER_WALK_FRAMES 2
#define PLAYER_ANIMATED true


	//	//Player Ashkan Test
	//#define PLAYER_PATH "assets/player_sheet.png"
	//#define PLAYER_TEX_SIZE 32
	//#define PLAYER_ANIMATED true
	//#define PLAYER_ANIM_SPEED 500
	//
	//#define PLAYER_IDLE_FRAMES 7
	//#define PLAYER_WALK_FRAMES 2
	//#define PLAYER_WALK_RIGHT_FRAMES 4
	//#define PLAYER_WALK_LEFT_FRAMES 4
	//#define PLAYER_WALK_BACK_FRAMES 3


#define PLAYER_ID 666
#define PLAYER_X (WIN_W/2 - PLAYER_W/2)
#define PLAYER_Y (WIN_H/2 - PLAYER_H/2)
#define PLAYER_H 64
#define PLAYER_W 64

//	MAP DEFINITION
#define MAP_PATH "assets/map.txt"
#define MAP_WIDTH 100
#define MAP_HEIGHT 100

// WINDOW DEFINITION
#define WIN_H 640
#define WIN_W 800

// ANIMATION DEFINITION
#define IDLE 0
#define WALK 1
#define WALK_R 2
#define WALK_L 3
#define WALK_B 4


