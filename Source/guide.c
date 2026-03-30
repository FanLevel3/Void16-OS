#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void drawGuide(SDL_Renderer* renderer, TTF_Font* font, int* isOpen) {
    if (isOpen == NULL || *isOpen == 0) return;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color blue = {0, 0, 200, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color green = {0, 200, 0, 255};
    // R, G, B, Alpha : Set Color
    // StartX, StartY, W, H : Rect
    SDL_Rect guideWindow = {370, 40, 250, 420};
    SDL_SetRenderDrawColor(renderer, 211, 211, 211 ,255);
    SDL_RenderFillRect(renderer, &guideWindow);

    SDL_Rect guideBar = {370, 40, 250, 30};
    SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, 255);
    SDL_RenderFillRect(renderer, &guideBar);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    for (int i = 0; i < 2; i++) {
        // Draw Thicker fucking border
        SDL_Rect borderRect = {guideWindow.x - i, guideWindow.y - i, guideWindow.w + (i * 2), guideWindow.h + (i * 2)};
        SDL_RenderDrawRect(renderer, &borderRect);
    }

    drawText(renderer, font, "Amber Manual", 385, 45, white);

    drawText(renderer, font, "- show \"text\"", 380, 90, black);
    drawText(renderer, font, "  Display message", 390, 110, black);

    drawText(renderer, font, "- clear", 380, 145, black);
    drawText(renderer, font, "  Clear terminal", 390, 165, black);

    drawText(renderer, font, "- Ctrl+M", 380, 200, black);
    drawText(renderer, font, "  Open terminal", 390, 220, black);

    drawText(renderer, font, "-------------------", 380, 250, black);

    drawText(renderer, font, "- F5  : Run C Code", 380, 280, black);
    drawText(renderer, font, "- F6  : Run Amber", 380, 310, black);

    drawText(renderer, font, "- Ctrl+Alt+A : AmberDocs", 380, 340, black);    

    drawText(renderer, font, "- Ctrl+Alt+M : MotionLab", 380, 365, black); 

    drawText(renderer, font, "-------------------", 380, 385, black);

    drawText(renderer, font, "Press Ctrl+G to Close", 385, 410, green);
}
