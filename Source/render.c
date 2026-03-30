#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "terminal.h"

// Screen Resolution
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
extern void drawMLT(SDL_Renderer* renderer, TTF_Font* font, int* isOpen);
extern void drawML(SDL_Renderer* renderer, TTF_Font* font, int* isOpen);
extern void drawGuide(SDL_Renderer* renderer, TTF_Font* font, int* isOpen);
void abc_run(const char* code, char* outputBuffer);
void run_compiler_bridge(const char* code, char* outputBuffer);

TTF_Font* font = NULL;
TTF_Font* font2 = NULL;
TTF_Font* font3 = NULL;

// Helper function to render text drawText(renderer, font, "text", x, y, color)
void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


int main(int argc, char* argv[]) {
    
    TTF_Init();

    font = TTF_OpenFont("fnt.ttf", 32);
    font2 = TTF_OpenFont("fnt.ttf", 16);
    font3 = TTF_OpenFont("fnt.ttf", 10);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Void16 OS", 
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // OS State Variables
        int running = 1;
    int isWindowOpen = 0; 
    SDL_Event event;

    //Color
    SDL_Color textColor = {255, 255, 255, 255};
	SDL_Color textColorBlack = {0, 0, 0, 255};
    SDL_Color textColorWhite = {255, 255, 255, 255};

    // StartX, StartY, Width, Height
    // UI Elements
    SDL_Rect taskbar = {0, 450, 640, 30}; 
    SDL_Rect startBT = {5, 455, 82, 20};
    SDL_Rect mlBT = {92, 455, 82, 20};
    SDL_Rect appWindow = {0, 0, 640, 450}; 
    SDL_Rect ideWindow = {10, 10, 620, 430};
    SDL_Rect titleBar = {10, 10, 620, 20};

    char terminalOutput[1024] = "Void16 Terminal is Ready...";
    char textBuffer[1024] = "";
    int cursorTimer = 0;
    int showCursor = 1;
    int cursorIndex = 0;
    int isTerminalOpen = 0;
    int isDragging = 0;
    int termX = 160, termY = 140;
    int dragOffX = 0, dragOffY = 0;
    int isGuideOpen = 0;
    int isMLOpen = 0;
    int isMLTOpen = 0;

    SDL_StartTextInput();

    // Main Loop
    while (running) {
        // Event Handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            if (isMLOpen) {
                if (event.key.keysym.sym == SDLK_q && (SDL_GetModState() & KMOD_CTRL)) {
                    printf("Ctrl+Q Pressed Terminal is coming...");
                    isMLTOpen = !isMLTOpen;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;

                if (isTerminalOpen &&  mx >= termX  && mx <= termX + 324 && my >= termY - 15 &&  my <= termY) {
                    isDragging = 1;
                    dragOffX = mx - termX;
                    dragOffY = my - termY;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                isDragging = 0;
            }

            if (event.type == SDL_MOUSEMOTION) {
                if (isDragging) {
                    termX = event.motion.x - dragOffX;
                    termY = event.motion.y - dragOffY;
                }
            }



            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_t && (SDL_GetModState() & KMOD_CTRL)) {
                    isTerminalOpen = !isTerminalOpen;
                }
                if (event.key.keysym.sym == SDLK_F5) {
                    run_compiler_bridge(textBuffer, terminalOutput);
                    isTerminalOpen = 1;
                    printf("F5 pressed, Compiling...\n");
                }

                if (event.key.keysym.sym == SDLK_F6) {
                    abc_run(textBuffer, terminalOutput);

                    isTerminalOpen = 1;
                    printf("F6 Pressed...Running abc...");
                }

                if (event.key.keysym.sym == SDLK_g && (SDL_GetModState() & KMOD_CTRL)) {
                    isGuideOpen = !isGuideOpen;
                }

                if (event.key.keysym.sym == SDLK_a && (SDL_GetModState() & KMOD_CTRL) && (SDL_GetModState() & KMOD_ALT)) {
                    isWindowOpen = !isWindowOpen;
                }

                if (event.key.keysym.sym == SDLK_m && (SDL_GetModState() & KMOD_CTRL) && (SDL_GetModState() & KMOD_ALT)) {
                    isMLOpen = !isMLOpen;
                }
            }


            // Mouse Click Handling
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Toggle IDE Window with Start Button
                if (mouseX >= startBT.x && mouseX <= (startBT.x + startBT.w) &&
                    mouseY >= startBT.y && mouseY <= (startBT.y + startBT.h)) {
                    isWindowOpen = !isWindowOpen; 
                }

                if (mouseX >= mlBT.x && mouseX <= (mlBT.x + mlBT.y) &&
                    mouseY >= mlBT.y && mouseY <= (mlBT.y + mlBT.h)){
                    isMLOpen = !isMLOpen;
                }
            }
			if (isWindowOpen) {

	    		if (event.type == SDL_KEYDOWN) {
	        		int len = strlen(textBuffer);
		    		if (event.key.keysym.sym  == SDLK_LEFT) {
                        if (cursorIndex > 0) cursorIndex--;
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT) {
                        if (cursorIndex < len) cursorIndex++;
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        if (cursorIndex > 0) {
                            for(int i = cursorIndex - 1; i < len; i++) {
                                textBuffer[i] = textBuffer[i + 1];
                            }
                            cursorIndex--;
                        }
                    }
					if (event.key.keysym.sym == SDLK_RETURN){
					     int len = strlen(textBuffer);
						 for(int i = len ; i >= cursorIndex; i--) {
                             textBuffer[i + 1] = textBuffer[i];
                         }
                         textBuffer[cursorIndex] = '\n';                         cursorIndex++;
					}
                }

                if (event.type == SDL_TEXTINPUT) {
                    int len = strlen(textBuffer);
                    for(int i = len ; i >= cursorIndex; i--) {
                        textBuffer[i + 1] = textBuffer[i];
                    }
                    textBuffer[cursorIndex] = event.text.text[0];
                    cursorIndex++;
                }
			}
        }
//
        // Rendering


        SDL_SetRenderDrawColor(renderer, 0, 0, 170, 255); // Background
        SDL_RenderClear(renderer);

        // Desktop Label
        drawText(renderer, font, "Void16 OS", 10, 10, textColor);	

        // Draw Taskbar
        SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
        SDL_RenderFillRect(renderer, &taskbar);

        // Draw Start Button
        SDL_SetRenderDrawColor(renderer, 0, 170, 0, 255);
        SDL_RenderFillRect(renderer, &startBT);
        
        drawText(renderer, font2, "AmberDocs", 7, 457, textColorBlack);

        SDL_SetRenderDrawColor(renderer, 170, 0, 0, 255);
        SDL_RenderFillRect(renderer, &mlBT);

        drawText(renderer, font2, "MotionLab", 94, 457, textColorWhite);

        // Draw IDE Window if open
        if (isWindowOpen) {

            // Main Window Background
            SDL_SetRenderDrawColor(renderer, 0, 0, 170, 255);
            SDL_RenderFillRect(renderer, &appWindow);

            // Window Border
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &appWindow);

            // Text Area
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &ideWindow);

            // Window Title Bar
            SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
            SDL_RenderFillRect(renderer, &titleBar);

	    	drawText(renderer, font2, "AmberDocs - Untitled.txt", 230, 12, textColor);

             int lineHeight = 20;
             int paddingX = 40;
             int paddingY = 40;
             int maxWidth = 610;
             int maxHeight = 430;

             int currentX = paddingX;
             int currentY = paddingY;
             int csPosX = paddingX;
             int csPosY = paddingY;
             //check new line loop
             for(int i = 0; i < (int)strlen(textBuffer); i++) {
                char c = textBuffer[i];
                char strC[2] = {c, '\0'};
                int w, h;
                TTF_SizeText(font2, strC, &w, &h);

                if (c == '\n' || currentX + w > maxWidth) {
                    currentX = paddingX;
                    currentY += lineHeight;

                    if (currentY + lineHeight > maxHeight) break;

                    if (c == '\n') {
                        if (i < cursorIndex) { csPosX = currentX; csPosY = currentY; }
                        continue;
                    }
                 }//first if
             

                if (i < cursorIndex) {
                    csPosX = currentX + w;
                    csPosY = currentY;
                }

                drawText(renderer, font2, strC, currentX, currentY, textColorBlack);
                currentX += w;
             }//for loop for check new line

			cursorTimer++;
			if (cursorTimer > 10) {
				showCursor = !showCursor;
				cursorTimer = 0;
			}

            if (showCursor) {
                int charW = 10;
                if (textBuffer[cursorIndex] != '\0' && textBuffer[cursorIndex] != '\n') {
                    char currentChar[2] = { textBuffer[cursorIndex], '\0' };
                    TTF_SizeText(font2, currentChar, &charW, NULL);
                }
            
                SDL_Rect cursorRect = {csPosX, csPosY, charW, 15};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &cursorRect);

                if (cursorIndex < (int)strlen(textBuffer) && textBuffer[cursorIndex] != '\n') {
                    char currentChar[2] = { textBuffer[cursorIndex], '\0' };
                    drawText(renderer, font2, currentChar, csPosX, csPosY, (SDL_Color){255, 255, 255, 255});
                }
            }//if show cursor close
            
        }//If window open CLose

        if (isTerminalOpen) {
            drawTerminal(renderer, font2, &isTerminalOpen, terminalOutput, termX, termY);
        }

        if (isGuideOpen) {
            drawGuide(renderer, font2, &isGuideOpen);
        }

        if (isMLOpen) {
            drawML(renderer, font, &isMLOpen);
        }

        if (isMLOpen && isMLTOpen) {
            drawMLT(renderer, font2, &isMLTOpen);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup Resources
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

