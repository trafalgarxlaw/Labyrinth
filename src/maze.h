#ifndef MAZE_H
#define MAZE_H

#include "utils.h"
#include "sdl2.h"
#include <stdbool.h>
#include <tmx.h>

// --------------- //
// Data structures //
// --------------- //

struct Maze {
    tmx_map *map;           // The TMX map
    struct Position start;  // The starting position
    struct Position end;    // The end position
    SDL_Texture *texture;   // The texture (image)
    SDL_Renderer *renderer; // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a maze from a TMX file.
 *
 * @param filename  The path of the TMX file
 * @param renderer  The renderer
 * @return          A pointer to the create maze, NULL if there was an error;
 *                  Call IMG_GetError() for more information.
 */
struct Maze *Maze_create(char *filename, SDL_Renderer *renderer);

/**
 * Delete the given maze.
 *
 * @param maze  The maze to be deleted
 */
void Maze_delete(struct Maze *maze);

/**
 * Renders the maze with a renderer.
 *
 * @param maze      The maze to be rendered
 */
void Maze_render(struct Maze *maze);

/**
 * Returns true if and only if there is a wall in the given direction.
 *
 * Warning: Assumes that the tiles' gid are enumerated in lexicographic
 * order with respect to the presence (1) or absence (0) of the right,
 * upper, left and lower wall respectively.
 *
 * @param maze       The maze
 * @param position   The position
 * @param direction  The direction to look at
 * @return           true if and only if there is a wall
 */
bool Maze_hasWall(struct Maze *maze,
                  struct Position position,
                  enum Direction direction);

#endif
