#include "maze.h"

/**
 * Generate the texture of the whole maze.
 *
 * @param maze  The maze whose texture is generated
 */
void Maze_generateTexture(struct Maze *maze);

static SDL_Renderer *Maze_renderer;

void* Maze_imageLoader(const char *path) {
    return IMG_LoadTexture(Maze_renderer, path);
}

// ---------------- //
// Public functions //
// ---------------- //

struct Maze *Maze_create(char *filename, SDL_Renderer *renderer) {
    // Warning: modifying global variables of TMX for loading map
    Maze_renderer = renderer;
    tmx_img_load_func = (void* (*)(const char*))Maze_imageLoader;
    tmx_img_free_func = (void  (*)(void*))      SDL_DestroyTexture;
    tmx_map *map = tmx_load(filename);

    if (!map) {
        return NULL;
    } else {
        struct Maze *maze;
        maze = (struct Maze*)malloc(sizeof(struct Maze));
        maze->map = map;
        maze->renderer = renderer;
        Maze_generateTexture(maze);
        return maze;
    }
}

void Maze_render(struct Maze *maze) {
    SDL_RenderCopy(maze->renderer, maze->texture, NULL, NULL);
}

bool Maze_hasWall(struct Maze *maze,
                  struct Position position,
                  enum Direction direction) {
    tmx_layer *layer = maze->map->ly_head;
    unsigned int gid = layer->content.gids[(position.row * maze->map->width)
                                           + position.col];
    switch (direction) {
        case DIRECTION_RIGHT:
            return (gid - 1) % 16 < 8;
            break;
        case DIRECTION_UP:
            return (gid - 1) % 8 < 4;
            break;
        case DIRECTION_LEFT:
            return (gid - 1) % 4 < 2;
            break;
        case DIRECTION_DOWN:
            return (gid - 1) % 2 < 1;
            break;
    }
}

void Maze_delete(struct Maze *maze) {
    if (maze != NULL) {
        if (maze->texture != NULL) {
            SDL_DestroyTexture(maze->texture);
            maze->texture = NULL;
        }
        tmx_map_free(maze->map);
        free(maze);
    }
}

// ----------------- //
// Private functions //
// ----------------- //

void Maze_generateTexture(struct Maze *maze) {
    tmx_map *map = maze->map;
    int textureWidth = map->width  * map->tile_width;
    int textureHeight = map->height * map->tile_height;
    maze->texture = SDL_CreateTexture(maze->renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        textureWidth, textureHeight);
    SDL_SetRenderTarget(maze->renderer, maze->texture);
    SDL_RenderClear(maze->renderer);
    tmx_layer *layer;
    for (layer = map->ly_head; layer; layer = layer->next) {
        unsigned int i, j;
        for (i = 0; i < map->height; i++) {
            for (j = 0; j < map->width; j++) {
                unsigned int gid;
                SDL_Rect srcrect, dstrect;
                SDL_Texture* texture;
                gid = layer->content.gids[(i * map->width) + j];
                tmx_image *image = map->tiles[gid]->image;
                image = map->tiles[gid]->image;
                srcrect.x = map->tiles[gid]->ul_x;
                srcrect.y = map->tiles[gid]->ul_y;
                srcrect.w = image->width;
                srcrect.h = image->height;
                dstrect.w = image->width;
                dstrect.h = image->height;
                dstrect.x = j * image->width;
                dstrect.y = i * image->height;
                texture = (SDL_Texture*)image->resource_image;
                SDL_RenderCopy(maze->renderer, texture, &srcrect, &dstrect);
            }
        }
    }
    SDL_SetRenderTarget(maze->renderer, NULL);
}
