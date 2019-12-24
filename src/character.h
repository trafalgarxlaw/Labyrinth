#ifndef CHARACTER_H
#define CHARACTER_H

#include "utils.h"
#include "maze.h"
#include "sdl2.h"
#include "animated_spritesheet.h"

// --------------- //
// Data structures //
// --------------- //

struct CharacterMove {
    struct Point source;      // The source position
    struct Point target;      // The target position
    enum Direction direction; // The direction of the move
    int startTime;            // The start time
    int endTime;              // The end time
    int duration;             // The total duration of the move
};

struct Character {
    struct AnimatedSpritesheet *animatedSpritesheet; // His spritesheet
    struct Point screenPosition;                     // His position in the screen
    struct Position mazePosition;                    // His position in the maze
    bool moving;                                     // True if currently moving
    struct CharacterMove currentMove;                // The current move
    SDL_Renderer *renderer;                          // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates the character.
 *
 * @param renderer   The renderer
 * @return           A pointer to the character, NULL if there was an error;
 *                   Call IMG_GetError() for more information.
 */
struct Character *Character_create(SDL_Renderer *renderer);

/**
 * Deletes the character.
 *
 * @param character  The character to delete
 */
void Character_delete(struct Character *character);

/**
 * Renders the character.
 *
 * @param character  The character to render
 */
void Character_render(struct Character *character);

/**
 * Moves the character.
 *
 * If the character is already moving, the present move is ignored.
 *
 * @param character  The character to move
 * @param direction  The direction of the move
 * @param duration   The time (in ms) of the whole move
 */
void Character_move(struct Character *character,
                    enum Direction direction,
                    int duration);

#endif
