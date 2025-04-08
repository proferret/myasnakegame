

#include "../include//apple.h"
#include "../include//window.h"
#include <stdbool.h>  // Add missing include for bool type
#include <stddef.h>
// Make sure we have access to COLS and ROWS definitions
#define COLS 32
#define ROWS 24
#define APPLE_SPAWN_DELAY 500  // Add missing definition

/**
 * @brief Initializes the apple object with a random position that is not on the snake's body.
 *
 * @param apple Pointer to the apple object to be initialized.
 * @param snake Pointer to the snake object.
 * @param timer Pointer to the timer object used to control apple spawning.
 */
void init_apple(Apple *apple, const Snake *snake, const Timer *timer) {
    apple->timer = *timer;

    do {
        apple->pos.x = (float) GetRandomValue(0, COLS - 1);
        apple->pos.y = (float) GetRandomValue(0, ROWS - 1);

        bool valid_pos = true;

        for (int i = 0; i < snake->length; i++) {
            if (apple->pos.x == snake->pos[i].x && apple->pos.y == snake->pos[i].y) {
                valid_pos = false;
                break;
            }
        }

        if (valid_pos) {
            break;
        }

    } while (true);
}

/**
 * @brief Spawns an apple on the game window.
 *
 * This function handles the spawning of the apple on the game window. It checks if the apple has been eaten and if the timer for spawning is done.
 * If the apple has been eaten and the timer is done, it resets the timer and re-initializes the apple with a new random position.
 * If the apple has not been eaten or the timer is not done, it simply draws the apple on the game window.
 * The function includes safety checks to prevent any rendering issues or potential segmentation faults.
 *
 * @param apple Pointer to the apple object.
 * @param snake Pointer to the snake object.
 */
void spawn_apple(Apple *apple, const Snake *snake) {
    // Safety check for null pointers
    if (apple == NULL || snake == NULL) {
        return;
    }
    
    // Validate snake length to prevent accessing out-of-bounds memory
    if (snake->length <= 0 || snake->length > 100) {
        return;
    }

    if (apple->first_render) {
        init_apple(apple, snake, &apple->timer);
        apple->first_render = false;
        apple->eaten = false;
    } else {
        if (apple->eaten && timer_done(&apple->timer)) {
            reset_timer(&apple->timer, APPLE_SPAWN_DELAY);
            init_apple(apple, snake, &apple->timer);
            apple->eaten = false;
        }
    }

    // Safety check for apple position before rendering
    if (apple->pos.x < 0 || apple->pos.x >= COLS || apple->pos.y < 0 || apple->pos.y >= ROWS) {
        // Attempt to recover by reinitializing the apple
        init_apple(apple, snake, &apple->timer);
    }

    if (!apple->timer.active || timer_done(&apple->timer))
        draw_textured_rectangle(apple->pos, apple->texture, WHITE);
}