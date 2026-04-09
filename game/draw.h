
#ifndef BALLZ_DRAW_H
#define BALLZ_DRAW_H

#include "def.h"

bool renderGame(ballsGame * game);
void renderCursor(ballsGame * game);
void renderBalls(ballsGame * game);
void drawText(ballsGame * game, char * text, int posx, int posy);
void drawShield(ballsGame * game);


#endif //BALLZ_DRAW_H
