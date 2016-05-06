//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class SDLInit{

public:
	bool Setup();
	bool FinalCleanup();
	bool Cleanup(SDL_Surface* surface);

	SDL_Surface* loadSurface(std::string path);

	void Update();

};