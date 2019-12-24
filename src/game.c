#include "game.h"
#include "sdl2.h"
#include "constants.h"

// --------------------------- //
// Private function prototypes //
// --------------------------- //
bool Game_validMove(struct Game *game, enum Direction direction);

struct Game *Game_initialize(SDL_Renderer *renderer) {
    struct Game *game;
    game = (struct Game*)malloc(sizeof(struct Game));
    game->renderer = renderer;
    game->maze = Maze_create(MAZE_FILENAME, renderer);
    game->character = Character_create(renderer);
    game->state = GAME_PLAY;
    return game;
}

void Game_delete(struct Game *game) {
    if (game != NULL) {
        Maze_delete(game->maze);
        Character_delete(game->character);
        free(game);
    }
}

void Game_run(struct Game *game) {
    SDL_Event e;
    while (game->state == GAME_PLAY) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                game->state = GAME_QUIT;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (Game_validMove(game, DIRECTION_LEFT)) {
                            Character_move(game->character,
                                           DIRECTION_LEFT,
                                           MOVE_DURATION);
                        }
                        break;
                    case SDLK_RIGHT:
                        if (Game_validMove(game, DIRECTION_RIGHT)) {
                            Character_move(game->character,
                                           DIRECTION_RIGHT,
                                           MOVE_DURATION);
                        }
                        break;
                    case SDLK_UP:
                        if (Game_validMove(game, DIRECTION_UP)) {
                            Character_move(game->character,
                                           DIRECTION_UP,
                                           MOVE_DURATION);
                        }
                        break;
                    case SDLK_DOWN:
                        if (Game_validMove(game, DIRECTION_DOWN)) {
                            Character_move(game->character,
                                           DIRECTION_DOWN,
                                           MOVE_DURATION);
                        }
                        break;
                }
            }
        }
        if (game->character->mazePosition.row == game->maze->map->height - 1 &&
            game->character->mazePosition.col == game->maze->map->width - 1) {
            game->state = GAME_MENU;
        }
        SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear(game->renderer);
        Maze_render(game->maze);
        Character_render(game->character);
        SDL_RenderPresent(game->renderer);
    }
}

bool Game_validMove(struct Game *game, enum Direction direction) {
    struct Position currentPosition = game->character->mazePosition;
    struct Position targetPosition = currentPosition;
    switch (direction) {
        case DIRECTION_RIGHT:
            ++targetPosition.col;
            break;
        case DIRECTION_UP:
            --targetPosition.row;
            break;
        case DIRECTION_LEFT:
            --targetPosition.col;
            break;
        case DIRECTION_DOWN:
            ++targetPosition.row;
            break;
    }
    return Maze_hasWall(game->maze, game->character->mazePosition, direction);
}
