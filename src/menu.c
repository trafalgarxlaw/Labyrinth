#include "menu.h"
#include "spritesheet.h"
#include "sdl2.h"

struct Menu *Menu_initialize(SDL_Renderer *renderer) {
    struct Menu *menu;
    menu = (struct Menu*)malloc(sizeof(struct Menu));
    menu->renderer = renderer;
    menu->choice = MENU_NONE;
    menu->title = Spritesheet_create(TITLE_FILENAME, 1, 1, 1, renderer);
    menu->play = Spritesheet_create(PLAY_FILENAME, 1, 1, 1, renderer);
    menu->quit = Spritesheet_create(QUIT_FILENAME, 1, 1, 1, renderer);
    return menu;
}

void Menu_run(struct Menu *menu) {
    SDL_Event e;
    while (menu->choice == MENU_NONE) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                menu->choice = MENU_QUIT;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_1:
                        menu->choice = MENU_PLAY;
                        break;
                    case SDLK_2:
                        menu->choice = MENU_QUIT;
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(menu->renderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear(menu->renderer);
        Spritesheet_render(menu->title, TITLE_X, TITLE_Y, 0);
        Spritesheet_render(menu->play, PLAY_X, PLAY_Y, 0);
        Spritesheet_render(menu->quit, QUIT_X, QUIT_Y, 0);
        SDL_RenderPresent(menu->renderer);
    }
}

void Menu_delete(struct Menu *menu) {
    if (menu != NULL) {
        Spritesheet_delete(menu->title);
        Spritesheet_delete(menu->play);
        Spritesheet_delete(menu->quit);
        free(menu);
    }
}
