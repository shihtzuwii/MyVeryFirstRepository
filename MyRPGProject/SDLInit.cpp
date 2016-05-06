#include "SDLInit.h"
bool sdlQuit = false;

static SDL_Event event;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* loadSurface(std::string path);
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
extern SDL_Surface* gPNGSurface;

bool SDLInit::Setup(){
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window				//TODO make this name global
		gWindow = SDL_CreateWindow("Arnachnid RPG!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);

			//Fill the surface white						//May wan to change color here
			Uint32 color = SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF);
			if (SDL_FillRect(gScreenSurface, NULL, color) < 0){
				printf("SDL rect could not be filled! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}



			else
			{
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				else
				{
					//Get window surface
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}
			}



		}
	}
	return success;
}

SDL_Surface* SDLInit::loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


//TODO add dleta time to this update function
void SDLInit::Update(){
	/* Poll for events */
	while (SDL_PollEvent(&event)){

		switch (event.type){
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */

			/* SDL_QUIT event (window close) */
		case SDL_QUIT:
			sdlQuit = true;
			break;

		default:
			break;
		}
		SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);

		SDL_UpdateWindowSurface(gWindow);
	}
	//TODO move tis code to an update function
	//Update the surface
	

}

bool SDLInit::Cleanup(SDL_Surface* surface){
	bool success = true;

	//Free loaded image
	SDL_FreeSurface(surface);
	surface = NULL;

	return success = false;
}

bool SDLInit::FinalCleanup(){
	bool success = true;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

	return success = false;
}