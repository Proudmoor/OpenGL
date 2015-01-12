#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>

#include <sstream>

Uint32 * pixels = new int[640*480];
void SetPixel(int x, int y) {
    pixels[y * 640 + x] = 0;
}

void DrawLine(int x0, int y0, int xEnd, int yEnd) {
    int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy,  deltaDyDx = 2 * (dy - dx);
    int x , y;

    if (x0 > xEnd) {
        x = xEnd; y = yEnd;
        xEnd = x0;
    } else {
        x = x0;
        y = y0;
    }

    SetPixel(x, y);

    while(x < xEnd) {
        x++;
        if (p < 0) 
            p += twoDy;
        else {
            y ++;
            p += deltaDyDx;
        }
        SetPixel(x, y);
    }
}


int main(int argc, char** argv) {
    bool quit = false;
    bool leftMouseButtonDown = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Draw Pixel", 
                            SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED, 
                            640, 480, 
                            0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STATIC,
                                640,480);
    
    memset(pixels, 255, 640 * 480 * sizeof(int));


     int ptCount = 0;
    while (!quit) {
        SDL_UpdateTexture(texture, NULL, pixels, 640*sizeof(int));
        SDL_WaitEvent(&event);
        int x1, y1;
        int x2, y2;
      
        switch(event.type){
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    leftMouseButtonDown = true;
                    if(ptCount == 0){
                        SDL_GetMouseState(&x1, &y1);
                        ptCount = 1;
                        //std::stringstream ss;
                        //ss << "X: " << x1 << " Y: " << y1;

                        //SDL_SetWindowTitle(window, ss.str().c_str());
                    } else {
                        SDL_GetMouseState(&x2, &y2);

                        std::stringstream ss;
                        ss << "a:" << x2 << "b:" << y2;
                        SDL_SetWindowTitle(window, ss.str().c_str());
                        ptCount = 0;

                        DrawLine(x1, y1, x2, y2);
                    }
                }
                

                


            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown){
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                   // pixels[mouseY * 640 + mouseX] = 0;
                }
            break;

            case SDL_QUIT:
                quit = true;
                break;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL,NULL);
        //SDL_RenderDrawLine(renderer,x1, y1, x2, y2);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}




















