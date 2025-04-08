#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "snake.h"
#include "timer.h"
#include "apple.h"

#define RESTART_MSG "Press enter to restart"
#define PAUSE_MSG "Game paused"
#define PAUSE_OVERLAY (Color) { 128, 128, 128, 128 }
#define FONT_SIZE 40

/**
 * @brief Enum representing the different states of the game.
 *
 * PLAYING: The game is currently in progress.
 * PAUSE: The game is paused.
 * OVER: The game is over.
 */
typedef enum {
    PLAYING,
    PAUSE,
    OVER,
} GameState;

void draw_grid(int cols, int rows, float cell_width, float cell_height);

void handle_keys(Snake *snake, GameState *state);

void update_game(Snake *snake, Apple *apple, GameState *state);

void draw_timer(const Timer *timer);

void restart_game(Snake *snake, GameState *state);

#endif
