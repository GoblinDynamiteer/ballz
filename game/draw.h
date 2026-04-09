
#ifndef BALLZ_DRAW_H
#define BALLZ_DRAW_H

#include "def.h"

bool draw_render_game(ballsGame * game);
void draw_render_cursor(ballsGame * game);
void draw_render_balls(ballsGame * game);
void draw_render_text(ballsGame * game, char * text, int posx, int posy);
void draw_render_shield(ballsGame * game);

#endif //BALLZ_DRAW_H
