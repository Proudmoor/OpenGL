#ifndef _SETUP_H
#define _SETUP_H

#include <SDL2/SDL.h>

class App {
private:
	bool Running;

	SDL_Surface* Surf_Display;
public:
	App();

	int OnExecute();
public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void OnRender();
	void OnCleanup();
};

#endif