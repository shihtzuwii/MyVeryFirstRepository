#include "SDLInit.h"
#include "GameManager.h"

bool sdlQuit = false;

float horizAxis = 0.0f;
float vertAxis = 0.0f;

static SDL_Event event;

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Surface* loadSurface(std::string path);
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;


bool SDLInit::Setup(){
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window				//TODO: Make this name global...
		gWindow = SDL_CreateWindow("Dragon Ball O!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
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
		Uint32 colorkey = SDL_MapRGB(gScreenSurface->format, 0, 0xFF, 0xFF);

		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, colorkey);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}


	return optimizedSurface;
}

void SDLInit::LoadTexture(Entity &entity) {
	//This is how we get our file name...
	const char* filePath = entity.mTextureName;

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
	}
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", filePath, SDL_GetError());
		}
		else {	//get image dimensions. Can call Entity.SetSize to override...
			entity.mWidth = loadedSurface->w;
			entity.mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	entity.mTexture = newTexture;
}

void SDLInit::Draw(Entity &entity){
	//SDL_BlitSurface(gPNGSurfaceGrass, NULL, gScreenSurface, NULL); // code that displays grass
	//Set rendering space and render to screen
	SDL_Rect renderRect = { (int)entity.mXPos, (int)entity.mYPos,
		entity.mWidth, entity.mHeight };

	//auto *anchorOffset = entity.GetAnchorOffset();

	////If the sprite size changes, the sprite will move. This offset
	////	is for anchoring the sprite, so that it doesn't move.
	//if (anchorOffset != NULL) {
	//	renderRect.x += anchorOffset->x;
	//	renderRect.y += anchorOffset->y;
	//}

	//Render to screen
	SDL_RenderCopy(gRenderer, entity.mTexture,
		NULL, &renderRect);
}

//TODO add dleta time to this update function
void SDLInit::Update(){
	//clearing out input values
	horizAxis = 0;
	vertAxis = 0;
	
	/* Poll for events */
	while (SDL_PollEvent(&event)){

		switch (event.type){
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */

			/* SDL_QUIT event (window close) */
			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym){
				case SDLK_LEFT:
					horizAxis = -1;
					break;
				case SDLK_RIGHT:
					horizAxis = 1;
					break;
				case SDLK_UP:
					vertAxis = -1;
					break;
				case SDLK_DOWN:
					vertAxis = 1;
					break;
				default:
					break;
				}
			}
			break;
			case SDL_QUIT:
				sdlQuit = true;
				break;

			default:
				break;
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	//TODO move tis code to an update function
	//Update the surface
	
	//MovePlayer(rectPlayer);
}

bool SDLInit::Cleanup(Entity &entity){
	bool success = true;

	//Free loaded image
	SDL_DestroyTexture(entity.mTexture);
	entity.mTexture = NULL;

	return success = false;
}

bool SDLInit::FinalCleanup(){
	bool success = true;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();

	return success = false;
}