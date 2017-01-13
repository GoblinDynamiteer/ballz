/*
 * main.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

#include "def.h"

int main(int argc, char *argv[]){
	/*	 Init SDL	*/
    SDL_Init(SDL_INIT_EVERYTHING);

    TTF_Init();

    /*	 Hide cursor	*/
    SDL_ShowCursor(SDL_DISABLE);

    /*	 Declare window and renderer	*/
    SDL_Window * window;
    SDL_Renderer * renderer;

    /*	 Create window	*/
	window = SDL_CreateWindow(
		"Ballz!",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIN_WIDTH,
		WIN_HEIGHT,
		WIN_FLAGS
	);

    /*	 Create renderer	*/
	renderer = SDL_CreateRenderer(
			window,
			-1,
			REN_FLAGS
	);


    /*	 Declare struct ballsGame	*/
    ballsGame ballsGame;
    ballsGame.window = window;
    ballsGame.renderer = renderer;

    /*	 Load game	*/
    loadGame(&ballsGame);

    while(processEvent(&ballsGame)){
    	renderGame(&ballsGame);
    	SDL_Delay(1000/60);
    }

    /*	 Quit SDL	*/
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(ballsGame.font);
    renderer = NULL;
    window = NULL;
    ballsGame.font = NULL;

	for(int i = 0; i<= DEVIL; i++){
		SDL_DestroyTexture(ballsGame.ballArt[i]);
		ballsGame.ballArt[i] = NULL;
	}

	for(int i = 0; i<= BLADE; i++){
		SDL_DestroyTexture(ballsGame.cursorArt[i]);
		ballsGame.cursorArt[i] = NULL;
	}

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

	return 0;
}
