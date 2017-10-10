/*
 * main.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

#include "def.h"

int main(int argc, char *argv[])
{
    /* Init SDL and SDL subsystems    */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    /* Hide cursor    */
    SDL_ShowCursor(SDL_DISABLE);

    /* Declare window and renderer    */
    SDL_Window * window;
    SDL_Renderer * renderer;

    /* Create window    */
    window = SDL_CreateWindow(
        "Ballz!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIN_WIDTH,
        WIN_HEIGHT,
        0x00 // Use WIN_FLAGS for full screen
    );

    /* Create renderer    */
    renderer = SDL_CreateRenderer(
            window,
            -1,
            REN_FLAGS
    );


    /* Declare struct ballsGame    */
    ballsGame ballsGame;
    ballsGame.window = window;
    ballsGame.renderer = renderer;

    /* Load game    */
    loadGame(&ballsGame);

    while(processEvent(&ballsGame)){
        renderGame(&ballsGame);
        SDL_Delay(1000/60);
    }


    for(int i = 0; i < MAX_BALLS; i++){
        free(ballsGame.balls[i]);
    }

    /* Quit SDL    */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(ballsGame.font);
    renderer = NULL;
    window = NULL;
    ballsGame.font = NULL;

    for(int i = 0; i < MAX_BALL_ART; i++){
        SDL_DestroyTexture(ballsGame.ballArt[i]);
        ballsGame.ballArt[i] = NULL;
    }

    for(int i = 0; i< MAX_GAME_TYPES; i++){
        SDL_DestroyTexture(ballsGame.cursorArt[i]);
        ballsGame.cursorArt[i] = NULL;
    }

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
