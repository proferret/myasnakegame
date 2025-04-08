#include "../include//score.h"
#include "raylib.h"
#include "../include//timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef _WIN32

#include <direct.h>
#include <stdlib.h>

#endif

/**
 * @brief Ensures that a directory exists. If it doesn't, it creates the directory.
 *
 * @param dir The path of the directory to be checked and created.
 *
 * @return void
 *
 * @note This function uses platform-specific functions to create directories.
 *       On Windows, it uses _mkdir(). On Unix-like systems, it uses mkdir().
 *
 * @warning This function does not handle errors in a robust manner. It simply prints a message
 *          to stdout and continues execution.
 *
 * @see https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/mkdir-wmkdir?view=msvc-170
 * @see https://pubs.opengroup.org/onlinepubs/9699919799/functions/mkdir.html
 */
void ensure_dir_exists(const char *dir) {
#ifdef _WIN32
    if (_mkdir(dir) == 0) {
        printf("INFO: Directory %s created\n", dir);
    }
#else
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
        printf("INFO: Directory %s created\n", dir);
    }
#endif
}

/**
 * @brief Initializes the score file.
 *
 * This function opens the score file in append mode and checks if it's empty.
 * If it is, it writes the initial score "0" to the file.
 * If the file does not exist, it calls the ensure_dir_exists function to create the necessary directory,
 * then opens the file in append mode and writes the initial score "0" to it.
 *
 * @return void
 *
 * @note This function uses the fopen, fseek, ftell, fgetc, fprintf, fclose, and ensure_dir_exists functions.
 *
 * @warning This function does not handle errors in a robust manner. It simply prints a message
 *          to stdout and continues execution.
 *
 * @see ensure_dir_exists
 * @see https://en.cppreference.com/w/c/io/fopen
 * @see https://en.cppreference.com/w/c/io/fseek
 * @see https://en.cppreference.com/w/c/io/ftell
 * @see https://en.cppreference.com/w/c/io/fgetc
 * @see https://en.cppreference.com/w/c/io/fprintf
 * @see https://en.cppreference.com/w/c/io/fclose
 */
void init_score(void) {
    FILE *f = fopen(SCORE_TXT_PATH, "a+");

    if (f != NULL) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);

        if (size == 0 || (size == 1 && fgetc(f) == '\n')) {
            fprintf(f, "0");
        }

        fclose(f);
        printf("INFO: %s initialized\n", SCORE_TXT_PATH);
    } else {
        ensure_dir_exists(SCORE_DIR_PATH);

        f = fopen(SCORE_TXT_PATH, "a+");

        if (f != NULL) {
            fseek(f, 0, SEEK_END);
            long size = ftell(f);

            if (size == 0 || (size == 1 && fgetc(f) == '\n')) {
                fprintf(f, "0");
            }

            fclose(f);
            printf("INFO: %s initialized\n", SCORE_TXT_PATH);
        } else {
            fprintf(stderr, IO_WARNING_1);
        }
    }
}


/**
 * @brief Loads the highest score from the score file.
 *
 * This function opens the score file in read mode, reads the first line,
 * converts it to a long integer, and returns it as the highest score.
 * If the file does not exist or cannot be opened, it prints an error message to stderr,
 * returns 0, and continues execution.
 * If the first line in the file cannot be converted to a valid integer,
 * it prints an error message to stderr, sets the highest score to -1,
 * and continues execution.
 *
 * @return The highest score as an integer. If the score file cannot be read or
 *         the first line cannot be converted to a valid integer, returns 0 or -1, respectively.
 *
 * @note This function uses the fopen, fgets, strtol, fprintf, fclose functions.
 *
 * @warning This function does not handle errors in a robust manner. It simply prints a message
 *          to stderr and continues execution.
 *
 * @see https://en.cppreference.com/w/c/io/fopen
 * @see https://en.cppreference.com/w/c/io/fgets
 * @see https://en.cppreference.com/w/c/string/byte/strtol
 * @see https://en.cppreference.com/w/c/io/fprintf
 * @see https://en.cppreference.com/w/c/io/fclose
 */
int load_highest_score(void) {
    FILE *f = fopen(SCORE_TXT_PATH, "r");

    if (f == NULL) {
        fprintf(stderr, IO_WARNING_2);
        return 0;
    }

    char buffer[100];
    if (fgets(buffer, sizeof(buffer), f) == NULL) {
        fprintf(stderr, IO_WARNING_2);
        fclose(f);
        return 0;
    }

    char *endptr;
    long highest_score = strtol(buffer, &endptr, 10);

    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, IO_WARNING_2);
        highest_score = -1;
    }

    fclose(f);

    return (int) highest_score;
}


/**
 * @brief Saves the highest score to the score file.
 *
 * This function compares the given score with the highest score loaded from the file.
 * If the given score is higher, it overwrites the content of the score file with the new score.
 * If the score file cannot be opened for writing, it prints an error message to stderr.
 *
 * @param score The current score to be saved.
 *
 * @return void
 *
 * @note This function uses the fopen, fprintf, fclose, load_highest_score functions.
 *
 * @warning This function does not handle errors in a robust manner. It simply prints a message
 *          to stderr and continues execution.
 *
 * @see load_highest_score
 * @see https://en.cppreference.com/w/c/io/fopen
 * @see https://en.cppreference.com/w/c/io/fprintf
 * @see https://en.cppreference.com/w/c/io/fclose
 */
void save_highest_score(int score) {
    int highest = load_highest_score();

    FILE *f = fopen(SCORE_TXT_PATH, "w");

    if (f == NULL) {
        fprintf(stderr, IO_WARNING_3);
        return;
    }

    if (score > highest)
        fprintf(f, "%d", score);
    else
        fprintf(f, "%d", highest);

    fclose(f);
}

/**
 * @brief Draws the current score and the highest score on the screen.
 *
 * This function uses raylib's DrawText function to display the current score and the highest score
 * on the screen at the specified positions. If the highest score is invalid (i.e., -1), it displays
 * an error message indicating that the score file is invalid.
 *
 * @param current_score The current score to be displayed.
 * @param highest_score The highest score to be displayed.
 *
 * @return void
 *
 * @note This function uses raylib's DrawText function.
 *
 * @warning This function does not handle errors in a robust manner. It simply prints a message
 *          to the screen and continues execution.
 *
 * @see https://www.raylib.com/cheatsheet/cheatsheet.html#DrawText
 */
void draw_score(int current_score, int highest_score) {
    DrawText(TextFormat("Current Score: %d", current_score), SCORE_POSX,
             SCORE_POSY, SCORE_FONTSIZE, BLACK);

    if (highest_score == -1) {
        DrawText(TextFormat("Highest Score: (-1) => \n\n%s is invalid", SCORE_TXT_PATH),
                 SCORE_POSX, SCORE_POSY + 30, SCORE_FONTSIZE, RED);
    } else {
        DrawText(TextFormat("Highest Score: %d", highest_score), SCORE_POSX,
                 SCORE_POSY + 30, SCORE_FONTSIZE, BLACK);
    }
}

/**
 * @brief Draws the elapsed time on the screen.
 *
 * This function uses raylib's DrawText function to display the elapsed time
 * on the screen at the specified position. The elapsed time is formatted as a string
 * with two decimal places.
 *
 * @param timer A pointer to the Timer structure that holds the elapsed time.
 *
 * @return void
 *
 * @note This function uses raylib's DrawText function.
 *
 * @warning This function does not handle errors in a robust manner. It simply prints a message
 *          to the screen and continues execution.
 *
 * @see https://www.raylib.com/cheatsheet/cheatsheet.html#DrawText
 */
void draw_timer(const Timer *timer) {
    char timer_text[64];
    sprintf(timer_text, "Elapsed Time: %.2f", timer->lifetime);
    DrawText(timer_text, 10, 80, 20, BLACK); // Adjust position as needed
}
