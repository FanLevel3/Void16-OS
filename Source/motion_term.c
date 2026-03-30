#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

extern TTF_Font* font2;
extern void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void drawMLT(SDL_Renderer* renderer, TTF_Font* font, int* isOpen) {
    
    SDL_Rect mlTermBg = {320, 240, 250, 100};
    SDL_Rect mlTermBar = {320, 220, 250, 20};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color blue = {0, 0, 170, 255};
    SDL_Color green = {0, 170, 0, 255};
    SDL_Color red = {170, 0, 0, 255};

    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, 255);
    SDL_RenderFillRect(renderer, &mlTermBg);

    SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, 255);
    SDL_RenderFillRect(renderer, &mlTermBar);

    drawText(renderer, font2, "MoionLab-Terminal", 360, 225, green);
    
}
