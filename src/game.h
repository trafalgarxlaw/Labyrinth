#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "character.h"

// --------------- //
// Data structures //
// --------------- //

enum GameState {
    GAME_PLAY, // The player is playing
    GAME_MENU, // The player is returning to the menu
    GAME_QUIT  // The player is quitting
};

struct Game {
    struct Maze *maze;           // The current maze
    struct Character *character; // The character
    SDL_Renderer *renderer;      // The renderer
    enum GameState state;        // The state of the game
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new game.
 *
 * @param   The renderer for the game
 * @return  A pointer to the game, NULL if there was an error
 */
struct Game *Game_initialize(SDL_Renderer *renderer);

/**
 * Delete the game.
 *
 * @param game  The game to delete
 */
void Game_delete(struct Game *game);

/**
 * Start running the game.
 *
 * @param game  The game to run
 */
void Game_run(struct Game *game);

#endif
