#include "../include//controllers.h"
#include "../include//window.h"
#include "raylib.h"
#include <stdbool.h>

/**
 * @brief Draws a grid on the screen.
 *
 * This function uses raylib's DrawRectangleLines function to draw a grid on the screen.
 * The grid is composed of cells, each with the specified width and height.
 *
 * @param cols The number of columns in the grid.
 * @param rows The number of rows in the grid.
 * @param cell_width The width of each cell in the grid.
 * @param cell_height The height of each cell in the grid.
 *
 * @return This function does not return any value.
 */
void draw_grid(int cols, const int rows, const float cell_width, float cell_height) {
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            DrawRectangleLines(i * cell_width, j * cell_height, (int) cell_width,
                               (int) cell_height, LIGHTGRAY);
        }
    }
}

/**
 * @brief Handles the key inputs for the snake game.
 *
 * This function checks if any of the arrow keys are pressed and updates the snake's direction accordingly.
 * It also handles the pause functionality when the spacebar is pressed.
 *
 * @param snake A pointer to the Snake struct representing the snake in the game.
 * @param state A pointer to the GameState enum representing the current state of the game.
 *
 * @return This function does not return any value.
 */
void handle_keys(Snake *snake, GameState *state) {
    if (IsKeyDown(KEY_SPACE)) {
        *state = PAUSE;
    } else if (IsKeyDown(KEY_RIGHT) && snake->direction != LEFT) {
        snake->direction = RIGHT;
        snake->has_moved = true;
    } else if (IsKeyDown(KEY_LEFT) && snake->direction != RIGHT) {
        snake->direction = LEFT;
        snake->has_moved = true;
    } else if (IsKeyDown(KEY_UP) && snake->direction != DOWN) {
        snake->direction = UP;
        snake->has_moved = true;
    } else if (IsKeyDown(KEY_DOWN) && snake->direction != UP) {
        snake->direction = DOWN;
        snake->has_moved = true;
    }
}


/**
 * @brief Updates the game state.
 *
 * This function handles the game logic, including snake movement, apple consumption, and game over conditions.
 * It also updates the apple timer and draws the snake.
 *
 * @param snake A pointer to the Snake struct representing the snake in the game.
 * @param apple A pointer to the Apple struct representing the apple in the game.
 * @param state A pointer to the GameState enum representing the current state of the game.
 *
 * @return This function does not return any value.
 */
void update_game(Snake *snake, Apple *apple, GameState *state) {
    Vector2 *snake_head = &snake->pos[0];
    Vector2 prev_pos[100];  // Store previous positions of all snake segments

    // Save current positions before any updates
    for (int i = 0; i < snake->length; i++) {
        prev_pos[i] = snake->pos[i];
    }

    // Check if the snake has moved
    if (snake->has_moved) {
        // Move the snake's body first (update all segments except the head)
        for (int i = snake->length - 1; i > 0; i--) {
            snake->pos[i] = prev_pos[i - 1];
        }

        // Update the head's position based on its direction
        switch (snake->direction) {
            case UP:
                snake_head->y -= 1;
                break;
            case DOWN:
                snake_head->y += 1;
                break;
            case LEFT:
                snake_head->x -= 1;
                break;
            case RIGHT:
                snake_head->x += 1;
                break;
            default:
                break;
        }
    }

    // Check if the snake has hit a wall or itself
    if (snake_head->x < 0 ||
        snake_head->x >= COLS ||
        snake_head->y < 0 ||
        snake_head->y >= ROWS) {
        // Set the game state to game over
        *state = OVER;
        return;
    }

    // Check if the snake has hit itself
    for (int i = 1; i < snake->length; i++) {
        if (snake_head->x == snake->pos[i].x && snake_head->y == snake->pos[i].y) {
            // Set the game state to game over
            *state = OVER;
            return;
        }
    }

    // Check if the snake has eaten the apple
    if (snake_head->x == apple->pos.x && snake_head->y == apple->pos.y) {
        // Reset the apple timer and play the eating sound
        start_timer(&apple->timer, apple->timer.lifetime);
        PlaySound(apple->eating_sound);
        // Increase the snake's score and length
        snake->score++;

        // Ensure we don't exceed our array bounds
        if (snake->length + 1 < 100) {
            // Add new segment at the end (copy last position)
            snake->pos[snake->length] = prev_pos[snake->length - 1];
            snake->length++;
        }

        // Mark the apple as eaten
        apple->eaten = true;
    }

    // Update the apple timer
    update_timer(&apple->timer);
    // Draw the snake
    draw_snake(snake);
}

/**
 * @brief Restarts the game by resetting the snake and changing the game state.
 *
 * This function initializes the snake using the init_snake function and sets the game state to PLAYING.
 *
 * @param snake A pointer to the Snake struct representing the snake in the game.
 * @param state A pointer to the GameState enum representing the current state of the game.
 *
 * @return This function does not return any value.
 */
void restart_game(Snake *snake, GameState *state) {
    init_snake(snake);
    *state = PLAYING;
}
