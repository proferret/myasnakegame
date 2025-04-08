#include "../include//snake.h"
#include "../include//window.h"
#include "raylib.h"
// Make sure we have access to COLS and ROWS definitions
#define COLS 32
#define ROWS 24

/**
 * @brief Initializes the snake game.
 *
 * This function sets the initial values for the snake's properties.
 * The length is set to 3 (considering the head), score is set to 0,
 * direction is set randomly, and the head position is set randomly within the game window.
 * The 'has_moved' flag is set to false to indicate that the snake has not moved yet.
 *
 * @param snake A pointer to the Snake struct that needs to be initialized.
 */
void init_snake(Snake *snake) {
    snake->length = 3; // Set initial length to 3 (head + 2 body segments)
    snake->score = 0;
    snake->direction = (Dir)GetRandomValue(0, 3);

    // Set the head position randomly
    snake->pos[0].x = (float)GetRandomValue(10, 22);
    snake->pos[0].y = (float)GetRandomValue(8, 16);

    // Initialize body parts relative to the head based on initial direction
    switch (snake->direction) {
        case UP:
            // Body segments are below the head
            snake->pos[1].x = snake->pos[0].x;
            snake->pos[1].y = snake->pos[0].y + 1;
            snake->pos[2].x = snake->pos[0].x;
            snake->pos[2].y = snake->pos[0].y + 2;
            break;
        case DOWN:
            // Body segments are above the head
            snake->pos[1].x = snake->pos[0].x;
            snake->pos[1].y = snake->pos[0].y - 1;
            snake->pos[2].x = snake->pos[0].x;
            snake->pos[2].y = snake->pos[0].y - 2;
            break;
        case LEFT:
            // Body segments are to the right of the head
            snake->pos[1].x = snake->pos[0].x + 1;
            snake->pos[1].y = snake->pos[0].y;
            snake->pos[2].x = snake->pos[0].x + 2;
            snake->pos[2].y = snake->pos[0].y;
            break;
        case RIGHT:
            // Body segments are to the left of the head
            snake->pos[1].x = snake->pos[0].x - 1;
            snake->pos[1].y = snake->pos[0].y;
            snake->pos[2].x = snake->pos[0].x - 2;
            snake->pos[2].y = snake->pos[0].y;
            break;
        default:
            break;
    }

    snake->has_moved = false;
}



/**
 * @brief Draws the snake on the screen.
 *
 * This function draws the snake on the screen using raylib's DrawRectangle function.
 * The snake is drawn as a series of rectangles, with the head having a different color than the body.
 * If the snake's score is greater than or equal to MIN_SCORE_FOR_RED_SNAKE, the snake and its head are drawn in red.
 * The function ensures proper rendering by drawing the body segments and head in the correct order.
 *
 * @param snake A pointer to the Snake struct that needs to be drawn.
 */
void draw_snake(Snake *snake) {
    Vector2 *head = &snake->pos[0];
    Color snake_color = LIME;
    Color head_color = DARKGREEN;

    if (snake->score >= MIN_SCORE_FOR_RED_SNAKE) {
        snake_color = RED;
        head_color = (Color) {204, 4, 4, 255}; // darker red
    }

    // Check if snake length is valid to prevent potential segmentation faults
    if (snake->length <= 0 || snake->length > 100) {
        return; // Invalid length
    }

    // Validate each snake position to prevent rendering issues
    for (int i = 0; i < snake->length; i++) {
        float x = snake->pos[i].x;
        float y = snake->pos[i].y;

        // Skip rendering if position is out of bounds
        if (x < 0 || x >= COLS || y < 0 || y >= ROWS) {
            continue;
        }

        // Draw each segment with safety checks
        if (i == 0) {  // Head segment
            DrawRectangle((int) (x * CELL_WIDTH), (int) (y * CELL_HEIGHT),
                         CELL_WIDTH, CELL_HEIGHT, head_color);
        } else {       // Body segments
            DrawRectangle((int) (x * CELL_WIDTH), (int) (y * CELL_HEIGHT),
                         CELL_WIDTH, CELL_HEIGHT, snake_color);
        }
    }
}


/**
 * @brief Draws a textured rectangle on the screen.
 *
 * This function uses raylib's DrawTexturePro function to draw a textured rectangle on the screen.
 * The rectangle is positioned based on the provided position, and its size is determined by the CELL_WIDTH and CELL_HEIGHT constants.
 * The texture, color tint, and other rendering properties can be customized using the provided parameters.
 *
 * @param position The position of the top-left corner of the rectangle on the screen.
 * @param texture The texture to be used for rendering the rectangle.
 * @param tint The color tint to be applied to the texture.
 *
 * @return This function does not return any value.
 */
void draw_textured_rectangle(Vector2 position, Texture2D texture, Color tint) {
    Rectangle dest_rect = {(float) (position.x * (float) CELL_WIDTH), (float) (position.y * (float) CELL_HEIGHT),
                           (float) CELL_WIDTH, (float) CELL_HEIGHT};
    Rectangle source_rect = {0, 0, (float) texture.width, (float) texture.height};
    Vector2 origin = {0, 0};
    DrawTexturePro(texture, source_rect, dest_rect, origin, 0, tint);
}
