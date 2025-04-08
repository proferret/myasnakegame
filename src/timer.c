#include "../include//timer.h"
#include "raylib.h"
#include <stdbool.h>

/**
 * @brief Starts the timer with the given duration.
 *
 * This function sets the timer's lifetime to the given duration and activates the timer.
 *
 * @param timer A pointer to the Timer struct to start.
 * @param lifetime The duration for which the timer should run.
 */
void start_timer(Timer *timer, const double lifetime) {
    timer->lifetime = lifetime;
    timer->active = true;
}

/**
 * @brief Resets the timer with the given duration.
 *
 * This function deactivates the timer, resets its lifetime to the given duration,
 * and prepares it for a new countdown.
 *
 * @param timer A pointer to the Timer struct to reset.
 * @param duration The duration for which the timer should run after reset.
 *
 * @return This function does not return any value.
 */
void reset_timer(Timer *timer, double duration) {
    timer->active = false;
    timer->lifetime = duration;
}

/**
 * @brief Updates the timer by subtracting the time elapsed since the last frame.
 *
 * This function checks if the timer is active and has a positive lifetime.
 * If both conditions are met, it decreases the lifetime by the time elapsed since the last frame.
 * This function is typically called in the game loop to keep the timer running accurately.
 *
 * @param timer A pointer to the Timer struct to update.
 *
 * @return This function does not return any value.
 */
void update_timer(Timer *timer) {
    if (timer->active && timer->lifetime > 0) {
        timer->lifetime -= GetFrameTime();
    }
}

bool timer_done(const Timer *timer) {
    return timer->lifetime <= 0;
}
