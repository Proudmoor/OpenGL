#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480
#define DEPTH 32







int main(int argc, char** argv) {
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * screen = SDL_CreateWindow("My SDL Empty Window", 
                            SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED, 
                            640, 480, 
                            0);
    while (!quit) {
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                break;
        }
    }

    SDL_Quit();
    return 0;
}




















