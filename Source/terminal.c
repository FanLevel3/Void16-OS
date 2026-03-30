#include "terminal.h"
#include <string.h>

extern void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void drawTerminal(SDL_Renderer* renderer, TTF_Font* font, int* isOpen, const char* output, int x, int y) {
    if (isOpen == NULL || *isOpen == 0) return;

    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    SDL_Rect term = {x, y, TERM_W, TERM_H};
    SDL_Rect termBar = {x - 2, y - 17, 324, 15};

    //White screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &term);
    //Blue Border
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    SDL_RenderDrawRect(renderer, &term);
    //TopBar black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &termBar);

    drawText(renderer, font, "Void16 OS Terminal 1.0", x + 42, y - 15, white);

    for (int i = 0; i < 3; i++) {
        SDL_Rect thickBorder = {term.x - i, term.y - i, term.w + (i * 2), term.h + (i * 2)};
        SDL_RenderDrawRect(renderer, &thickBorder);
    }

    if (output != NULL && strlen(output) > 0) {
        drawText(renderer, font,  output, term.x + 10, term.y + 10, black);
    }
}
