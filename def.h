/*
 * def.h
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

/*	 Include guard	*/
#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

/*	 Window dimensions, FULL HD!	*/
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

/*	 Flags for window	*/
#define WIN_FLAGS 0//SDL_WINDOW_FULLSCREEN
#define REN_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

/*	 Max balls on screen	*/
#define MAX_BALLS 5000

/*	 Balls per "tick" of spray (right button)	*/
#define BALLS_PER_SPRAY 3

/*	 Ball art size. Height == Width	*/
#define BALL_SIZE 50

/*	 Ball movement speed & acceleration	*/
#define MAXSPEED 15.0
#define ACC 1.005

/*	 Radius for magnet and repel	*/
#define MAG_RADIUS 500
#define MAGSTR 6.5
#define REPEL_RADIUS 350

#define KILLSIZE 45

/*	 Font stuff	*/
#define FONT_SIZE 28

/*	 Cursor stuff	*/
/*	 Blade mode rotation	*/
#define BLADE_SPEED 10.5

/*	 Game modes // Cursors	*/
enum {NORMAL, MAGNET, REPEL, BLADE, NEO, MAX_GAME_TYPES};

/*	 Ball colors, for texture array index	*/
enum {RED, YELLOW, BLUE, GREEN, SMILEY, PURPLE, DEVIL, MAX_BALL_ART};

enum {VERTICAL, HORIZONTAL};

/*	 Struct definitions	*/
typedef struct velocity{
	float x, y;
}velocity;

typedef struct pos{
	int x, y;
}position;

typedef struct ball{
	short color;
	bool active;
	SDL_Rect rect;
	velocity speed;
	double angle;
}ball;

typedef struct ballsGame{
	SDL_Window * window;
	SDL_Renderer * renderer;
	ball * balls[MAX_BALLS];
	SDL_Texture * cursorArt[MAX_GAME_TYPES];
	SDL_Texture * shield;
	position cursor;
	double cursorAngle;
	short mode;
	TTF_Font *font;
	int createdBalls;
	int killedBalls;
	int grabbedBallIndex;
	SDL_Texture * ballArt[MAX_BALL_ART];
	int shieldFrame;
	Uint64 ticker;
	char * modeText[MAX_GAME_TYPES];
}ballsGame;


/*	 Function definitions	*/

/*	 load.c	*/
bool loadGame(ballsGame * game);

/*	 event.c	*/
bool processEvent(ballsGame * game);
float getRandomDirection(void);
void cycleGameMode(ballsGame * game, bool upDown);
double calculateDistance(int x1, int x2, int y1, int y2);

/*	 balls.c	*/
bool addBall(ballsGame * game, int x, int y);
void moveBall(ballsGame * game, int i);
void rotateBall(ballsGame * game, int i);
void accelBall(ballsGame * game, int i);
void borderCheck(ballsGame * game, int i);
void huntCursor(ballsGame * game, int i);
void avoidCursor(ballsGame * game, int i);
void destroyBall(ballsGame * game, int i);
void killBalls(ballsGame * game, int i);
void flipBallSpeed(ballsGame * game, int i, bool direction);
void freezeBalls(ballsGame * game, int i);
int grabBall(ballsGame * game);

/*	 draw.c	*/
bool renderGame(ballsGame * game);
void renderCursor(ballsGame * game);
void renderBalls(ballsGame * game);
void drawText(ballsGame * game, char * text, int posx, int posy);
void drawShield(ballsGame * game);


#endif /* DEF_H_ */
