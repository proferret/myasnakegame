#ifndef APPLE_H
#define APPLE_H

#include "snake.h"

#define APPLE_TEXTURE_PATH WDIR "assets/apple.png"
#define APPLE_SOUND_PATH   WDIR "assets/apple.wav"
#define APPLE_SPAWN_DELAY 1.0
typedef struct {
    Texture2D texture;
    Sound eating_sound;
    Vector2 pos;
    bool eaten;
    bool first_render;
    Timer timer;
} Apple;

void init_apple(Apple *apple, const Snake *snake, const Timer *timer);

void spawn_apple(Apple *apple, const Snake *snake);

#endif
