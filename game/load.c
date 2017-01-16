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
	const char * imageFiles[] = {
			"art/ball_red.png",
			"art/ball_yellow.png",
			"art/ball_blue.png",
			"art/ball_green.png",
			"art/ball_smiley.png",
			"art/ball_purple.png",
			"art/ball_devil.png"
	};

	SDL_Surface * surface = NULL;

	for(int i = 0; i< MAX_BALL_ART; i++){
		surface = IMG_Load(imageFiles[i]);
		game->ballArt[i] = SDL_CreateTextureFromSurface(
				game->renderer, surface);
	}

	/*	Load cursor texture and set rectangle	*/
	/*	index: NORMAL, MAGNET, REPEL, BLADE, NEO */
	const char * imageFilesCursor[] = {
		"art/cursor.png",
		"art/cursor_magnet.png",
		"art/cursor_rep.png",
		"art/cursor_blade.png",
		"art/cursor_neo.png"
	};

	const char * tempName[] = {
		"NORMAL",
		"MAGNET",
		"REPEL",
		"BLADE",
		"NEO"
	};

	for(int i = 0; i< MAX_GAME_TYPES; i++){
		surface = IMG_Load(imageFilesCursor[i]);
		game->cursorArt[i] = SDL_CreateTextureFromSurface(
				game->renderer, surface);

		/*	 Copy mode names to char pointer array	*/
		int len = strlen(tempName[i]);
		game->modeText[i] = malloc(sizeof(char)*len+1);
		strcpy(game->modeText[i], tempName[i]);
		strcat(game->modeText[i], "\0");
	}

	/*	 Load shield bubble	*/
	surface = IMG_Load("art/cursor_shield_anim.png");
	game->shield = SDL_CreateTextureFromSurface(
			game->renderer, surface);

	/*	 Free surfaces	*/
	SDL_FreeSurface(surface);

	game->cursorAngle = 0.0;
	game->mode = NORMAL;
	game->createdBalls = 0;
	game->ticker = 0;
	game->killedBalls = 0;
	game->shieldFrame = 0;

	game->font = TTF_OpenFont("font/joystix_monospace.ttf", FONT_SIZE);

	return 1;
}
