#ifndef TERMINAL_H
#define TERMINAL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define TERM_W 320
#define TERM_H 200


void drawTerminal(SDL_Renderer* renderer, TTF_Font* font, int* isOpen, const char* output, int x, int y);

#endif
