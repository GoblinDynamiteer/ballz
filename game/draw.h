
#ifndef BALLZ_DRAW_H
#define BALLZ_DRAW_H

#include "def.h"

bool draw_render_game(Game *game);
void draw_render_cursor(Game *game);
void draw_render_balls(Game *game);
void draw_render_text(Game *game, char *text, int posx, int posy);
void draw_render_shield(Game *game);

#endif // BALLZ_DRAW_H
