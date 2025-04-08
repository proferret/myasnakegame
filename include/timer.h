#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

/**
 * @brief A structure representing a timer with a lifetime and an active state.
 */
typedef struct {
    double lifetime;
    bool active;
} Timer;

void start_timer(Timer *timer, double lifetime);

void reset_timer(Timer *timer, double duration);

void update_timer(Timer *timer);

bool timer_done(const Timer *timer);

#endif
