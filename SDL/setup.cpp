#include "setup.h"
#include <iostream>

App::App() {
	Surf_Display = NULL;
	Running = true;
}

int App::OnExecute() {
	if(OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	while(Running) {
		while(SDL_PollEvent(&Event)) {
			OnEvent(&Event);
			std::cout <<"Hello world" << std::endl;
		}
	    //std::cout <<"Hello world" << std::endl;
		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}

bool App::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}
	
	SDL_Window * screen = SDL_CreateWindow("My Game Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(!screen) {
		return false;
	}
	return true;
}

void App::OnEvent(SDL_Event* Event) {
	if(Event -> type == SDL_QUIT) {
		Running = false;
	}
}

void App::OnLoop() {

}

void App::OnRender() {

}

void App::OnCleanup() {
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	App theApp;
	std::cout << "Hello" << std::endl;
	return theApp.OnExecute();
}