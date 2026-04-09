#include <stdlib.h>
#include <time.h>

#include <SDL_image.h>

#include "def.h"

bool load_game(ballsGame *game) {

    /* Random seed */
    srand((int)time(NULL));

    /* Set starting ball array to NULL */
    for (int i = 0; i < MAX_BALLS; i++) {
        game->balls[i] = NULL;
    };

    /* Loads the ball texture */
    /* index: RED, YELLOW, BLUE, GREEN, SMILEY, PURPLE, DEVIL */
    const char *imageFiles[] = {
        BALLZ_ASSET_DIR "art/ball_red.png",    BALLZ_ASSET_DIR "art/ball_yellow.png",
        BALLZ_ASSET_DIR "art/ball_blue.png",   BALLZ_ASSET_DIR "art/ball_green.png",
        BALLZ_ASSET_DIR "art/ball_smiley.png", BALLZ_ASSET_DIR "art/ball_purple.png",
        BALLZ_ASSET_DIR "art/ball_devil.png"};

    SDL_Surface *surface = NULL;

    for (int i = 0; i < MAX_BALL_ART; i++) {
        surface = IMG_Load(imageFiles[i]);
        game->ballArt[i] = SDL_CreateTextureFromSurface(game->renderer, surface);
    }

    /* Load cursor texture and set rectangle */
    /* index: NORMAL, MAGNET, REPEL, BLADE, NEO */
    const char *imageFilesCursor[] = {
        BALLZ_ASSET_DIR "art/cursor.png", BALLZ_ASSET_DIR "art/cursor_magnet.png",
        BALLZ_ASSET_DIR "art/cursor_rep.png", BALLZ_ASSET_DIR "art/cursor_blade.png",
        BALLZ_ASSET_DIR "art/cursor_neo.png"};

    const char *tempName[] = {"NORMAL", "MAGNET", "REPEL", "BLADE", "NEO"};

    for (int i = 0; i < MAX_GAME_TYPES; i++) {
        surface = IMG_Load(imageFilesCursor[i]);
        game->cursorArt[i] = SDL_CreateTextureFromSurface(game->renderer, surface);

        /* Copy mode names to char pointer array */
        size_t len = strlen(tempName[i]);
        game->modeText[i] = malloc(len + 1);

        memcpy(game->modeText[i], tempName[i], len + 1);
    }

    /* Load shield bubble */
    surface = IMG_Load(BALLZ_ASSET_DIR "art/cursor_shield_anim.png");
    game->shield = SDL_CreateTextureFromSurface(game->renderer, surface);

    /* Free surfaces */
    SDL_FreeSurface(surface);

    game->cursorAngle = 0.0;
    game->mode = NORMAL;
    game->createdBalls = 0;
    game->ticker = 0;
    game->killedBalls = 0;
    game->shieldFrame = 0;

    game->font = TTF_OpenFont(BALLZ_ASSET_DIR "font/joystix_monospace.ttf", FONT_SIZE);

    return 1;
}
