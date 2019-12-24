#ifndef MENU_H
#define MENU_H

#include "sdl2.h"
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //

enum MenuChoice {
    MENU_NONE, // User has not made a choice
    MENU_QUIT, // User wishes to quit
    MENU_PLAY  // User wishes to play
};

struct Menu {
    enum MenuChoice choice;    // The choice of the user
    struct Spritesheet *title; // The title sprite
    struct Spritesheet *play;  // The play sprite
    struct Spritesheet *quit;  // The quit sprite
    SDL_Renderer *renderer;    // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new menu.
 *
 * @param renderer  The renderer
 * @return          A pointer to the menu, NULL if there was an error
 */
struct Menu *Menu_initialize(SDL_Renderer *renderer);

/**
 * Start running the menu.
 *
 * @param menu  The menu to show
 */
void Menu_run(struct Menu *menu);

/**
 * Delete the menu.
 *
 * @param menu  The menu to delete
 */
void Menu_delete(struct Menu *menu);

#endif
