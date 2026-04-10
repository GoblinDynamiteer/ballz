/*
 * main.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

#include <SDL_image.h>

#include "def.h"
#include "draw.h"
#include "event.h"
#include "load.h"

#define SDL_WINDOW_FLAGS (0x00) // Windowed Mode
#define SDL_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
/* -1 initializes the first driver supporting the requested flags. */
#define SDL_RENDERER_DRIVER_INDEX (-1)

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    /* Init SDL and SDL subsystems    */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    /* Hide cursor    */
    SDL_ShowCursor(SDL_DISABLE);

    SDL_Window *window =
        SDL_CreateWindow("Ballz!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                         WINDOW_HEIGHT, SDL_WINDOW_FLAGS);

    /* Create renderer    */
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, SDL_RENDERER_DRIVER_INDEX, SDL_RENDERER_FLAGS);

    Game game;
    game.window = window;
    game.renderer = renderer;

    /* Load game    */
    load_game(&game);

    while (event_process_events(&game)) {
        draw_render_game(&game);
        SDL_Delay(1000 / 60);
    }

    for (int i = 0; i < MAX_BALLS; i++) {
        free(game.balls[i]);
    }

    /* Quit SDL    */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(game.font);
    renderer = NULL;
    window = NULL;
    game.font = NULL;

    for (int i = 0; i < MAX_BALL_ART; i++) {
        SDL_DestroyTexture(game.ballArt[i]);
        game.ballArt[i] = NULL;
    }

    for (int i = 0; i < MAX_GAME_TYPES; i++) {
        SDL_DestroyTexture(game.cursorArt[i]);
        game.cursorArt[i] = NULL;
    }

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
