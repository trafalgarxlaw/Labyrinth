#include "constants.h"
#include "character.h"

struct Character *Character_create(SDL_Renderer *renderer) {
    struct Character *character;
    character = (struct Character*)malloc(sizeof(struct Character));
    character->renderer = renderer;
    character->moving = false;
    character->screenPosition.x = MAZE_INITIAL_X;
    character->screenPosition.y = MAZE_INITIAL_Y;
    character->mazePosition.row = 0;
    character->mazePosition.col = 0;
    character->animatedSpritesheet =
        AnimatedSpritesheet_create(CHARACTER_SPRITESHEET, 4, 20, 80,
            CHARACTER_BETWEEN_FRAME, renderer);
    character->animatedSpritesheet->spritesheet->scale = CHARACTER_SCALE;
    return character;
}

void Character_delete(struct Character *character) {
    if (character != NULL) {
        AnimatedSpritesheet_delete(character->animatedSpritesheet);
        free(character);
    }
}

void Character_render(struct Character *character) {
    if (character->moving) {
        int now = SDL_GetTicks();
        if (now > character->currentMove.endTime) {
            character->moving = false;
            switch (character->currentMove.direction) {
                case DIRECTION_RIGHT: character->mazePosition.col += 1; break;
                case DIRECTION_UP:    character->mazePosition.row -= 1; break;
                case DIRECTION_LEFT:  character->mazePosition.col -= 1; break;
                case DIRECTION_DOWN:  character->mazePosition.row += 1; break;
            }
            AnimatedSpritesheet_stop(character->animatedSpritesheet);
            character->screenPosition = character->currentMove.target;
        } else {
            float t = (now - character->currentMove.startTime) /
                       (float)character->currentMove.duration;
            character->screenPosition.x = (1 - t) * character->currentMove.source.x +
                                           t      * character->currentMove.target.x;
            character->screenPosition.y = (1 - t) * character->currentMove.source.y +
                                           t      * character->currentMove.target.y;
        }
    }
    AnimatedSpritesheet_render(character->animatedSpritesheet,
                               character->screenPosition.x,
                               character->screenPosition.y);
}

void Character_move(struct Character *character,
                    enum Direction direction,
                    int duration) {
    if (!character->moving) {
        character->moving = true;
        int now = SDL_GetTicks();
        character->currentMove.startTime = now;
        character->currentMove.duration = duration;
        character->currentMove.endTime = now + duration;
        character->currentMove.direction = direction;
        character->currentMove.source = character->screenPosition;
        character->currentMove.target = character->screenPosition;
        switch (direction) {
            case DIRECTION_RIGHT:
                character->currentMove.target.x += CHARACTER_HORIZONTAL_STEP;
                AnimatedSpritesheet_setRow(character->animatedSpritesheet,
                                           CHARACTER_WALKING_RIGHT_ROW);
                break;
            case DIRECTION_UP:
                character->currentMove.target.y -= CHARACTER_VERTICAL_STEP;
                AnimatedSpritesheet_setRow(character->animatedSpritesheet,
                                           CHARACTER_WALKING_UP_ROW);
                break;
            case DIRECTION_LEFT:
                character->currentMove.target.x -= CHARACTER_HORIZONTAL_STEP;
                AnimatedSpritesheet_setRow(character->animatedSpritesheet,
                                           CHARACTER_WALKING_LEFT_ROW);
                break;
            case DIRECTION_DOWN:
                character->currentMove.target.y += CHARACTER_VERTICAL_STEP;
                AnimatedSpritesheet_setRow(character->animatedSpritesheet,
                                           CHARACTER_WALKING_DOWN_ROW);
                break;
        }
        AnimatedSpritesheet_run(character->animatedSpritesheet);
    }
}
