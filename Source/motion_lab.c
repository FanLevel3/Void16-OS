#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

extern TTF_Font* font2;
extern void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void drawML(SDL_Renderer* renderer, TTF_Font* font, int* isOpen) {
    if(isOpen == NULL || *isOpen == 0) return;

    static float simTime = 0.0f;

    //I will draw a curve line first i think
    float u = 80.0f;
    float angle = 40.0f;
    float g = 9.8f;
    float rad = angle * (M_PI / 180.0f); // i think
    int startX = 50;
    int startY = 380;

        
    SDL_Rect mlBg = {0, 0, 640, 450};
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blue = {0, 0, 170, 255};
    SDL_Color green = {0, 200, 0, 255};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &mlBg);

    drawText(renderer, font, "MotionLab v1.0",200, 10, white);


    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderDrawLine(renderer, startX, startY, startX + 500, startY);// X line
    SDL_RenderDrawLine(renderer, startX, startY, startX, startY - 300);// Y line


    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
    for (float t = 0; t < simTime; t += 0.02f) {
        float x = u * cos(rad) * t;
        float y = (u * sin(rad) * t) - (0.5f * g * t * t);

        int drawX = startX + (int)x;
        int drawY = startY - (int)y;

        if (drawY > startY || drawX > 640) break;

        SDL_RenderDrawPoint(renderer, drawX, drawY);
        SDL_RenderDrawPoint(renderer, drawX + 1, drawY);
    }

    float curX = u * cos(rad) * simTime;
    float curY = (u * sin(rad) * simTime) - (0.5f * g * simTime * simTime);

    int ballX = startX + (int)curX;
    int ballY = startY - (int)curY;

    SDL_Rect ball = {ballX - 4, ballY - 4, 8, 8};
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_RenderFillRect(renderer, &ball);

    simTime += 0.04f;

    if (ballY > startY) {
        simTime = 0.f;
    }

}
