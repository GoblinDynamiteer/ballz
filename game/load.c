/*
 * load.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */


#include "..\def.h"

bool loadGame(ballsGame * game){

	/*	 Random seed	*/
	srand((int)time(NULL));

	/*	 Set starting ball array to NULL	*/
	for(int i = 0; i< MAX_BALLS; i++){
		game->balls[i] = NULL;
	};


	/*	 Loads the ball texture	*/
	/*	index: RED, YELLOW, BLUE, GREEN, SMILEY, PURPLE, DEVIL */
	char * imageFiles[] = {
			"art/ball_red.png",
			"art/ball_yellow.png",
			"art/ball_blue.png",
			"art/ball_green.png",
			"art/ball_smiley.png",
			"art/ball_purple.png",
			"art/ball_devil.png"
	};

	SDL_Surface * surface = NULL;

	for(int i = 0; i<= DEVIL; i++){
		surface = IMG_Load(imageFiles[i]);
		game->ballArt[i] = SDL_CreateTextureFromSurface(
				game->renderer, surface);
	}

	/*	Load cursor texture and set rectangle	*/
	/*	index: NORMAL, MAGNET, REPEL */
	char * imageFilesCursor[] = {
			"art/cursor.png",
			"art/cursor_magnet.png",
			"art/cursor_rep.png",
			"art/cursor_blade.png"
	};

	for(int i = 0; i<= BLADE; i++){
		surface = IMG_Load(imageFilesCursor[i]);
		game->cursorArt[i] = SDL_CreateTextureFromSurface(
				game->renderer, surface);
	}

	/*	 Load shield bubble	*/
	surface = IMG_Load("art/cursor_shield.png");
	game->shield = SDL_CreateTextureFromSurface(
			game->renderer, surface);

	/*	 Free surfaces	*/
	SDL_FreeSurface(surface);

	game->cursorAngle = 0.0;
	game->mode = NORMAL;
	game->ballIndex = 0;

	game->killedBalls = 0;

	game->font = TTF_OpenFont("font/joystix_monospace.ttf", FONT_SIZE);

	return 1;
}
