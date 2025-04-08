
#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include "timer.h"
#include "working_dir.h"

#define MIN_SCORE_FOR_RED_SNAKE 50



/**
 * @brief Structure representing the snake in the game.
 *
 * This structure holds the necessary information to manage the snake's state in the game.
 * It includes the positions of the snake's body parts, the current direction of the snake's head,
 * the current length of the snake, the current score of the snake, and a flag to indicate whether
 * the snake has moved in the current frame.
 */
typedef struct {
    Vector2 pos[100];  // Array to store the positions of the snake's body parts.
    Dir direction;     // The current direction of the snake's head.
    int length;        // The current length of the snake.
    int score;         // The current score of the snake.
    bool has_moved;    // A flag to indicate whether the snake has moved in the current frame.
} Snake;


void init_snake(Snake *snake);

void draw_snake(Snake *snake);

void draw_textured_rectangle(Vector2 position, Texture2D texture, Color tint);

#endif
