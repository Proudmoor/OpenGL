#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>

#include <sstream>

int * pixels = new int[640*480];
void SetPixel(int x, int y) {
    pixels[(y-1) * 640 + x] = 0;
}

void DrawLine(int x0, int y0,  int xEnd,  int yEnd) {
    const bool steep = (fabs(yEnd - y0) > fabs(xEnd - x0)); //whether the slope greater than 1
    // const bool horz = fabs(yEnd - y0); // whether is a horizontal line
    // const bool vert = fabs (xEnd - x0); // whether is a vertical line
    if (steep) {
        std::swap(x0, y0);
        std::swap(xEnd, yEnd);
    }

    if (x0 > xEnd){
        std::swap(x0, xEnd);
        std::swap(y0, yEnd);
    }

    const int dx = xEnd - x0; // xEnd always greater than x0
    const int dy = fabs(yEnd - y0);
    float error = dx /2.0f;
    const int ystep = (y0 < yEnd) ? 1: -1;
    int y = y0;

    const int maxX = xEnd;
    //draw point 
    if (x0 == xEnd & y0 == yEnd) SetPixel(x0,y0); 
    for (int x = x0; x < maxX; x++){
        if (steep){
            SetPixel(y, x);
        } else {
            SetPixel(x, y);
        }

        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
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


    bool ptCount = false; // whether have a point 
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
                        std::stringstream ss;
                        ss << "  X1:" << x2 << "  X1:" << y2;
                        SDL_SetWindowTitle(window, ss.str().c_str());
                        ptCount = true;
                    } else {
                        SDL_GetMouseState(&x2, &y2);

                        std::stringstream ss;
                        ss << "X2:" << x2 << "  X2:" << y2;
                        SDL_SetWindowTitle(window, ss.str().c_str());
                        ptCount = false;
                        DrawLine(x1, y1, x2, y2);
                    }
                }
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown){
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                }
            break;

            case SDL_QUIT:
                quit = true;
                break;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL,NULL);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}




















