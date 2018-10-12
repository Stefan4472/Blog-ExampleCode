// tests drawing textures from the TextureAtlas
// Compilation: g++ main.cpp texture_atlas.cpp -o test_texture_atlas -lSDL2 -lSDL2_image -std=c++11
// Execution: ./test_texture_atlas
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdexcept>
#include "texture_ids.h"
#include "texture_atlas.h"

using namespace std;

// function declarations (implemented below)
bool init();
bool loadMedia();
SDL_Texture* loadTexture(string path);
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* textureAtlasImg = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main()
{
  init();
  loadMedia();

  // create texture atlas
  TextureAtlas t_atlas = TextureAtlas(textureAtlasImg);

  // fill screen with black -- NOTE: not strictly necessary for this example
  SDL_Rect screen_background { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderFillRect(gRenderer, &screen_background);

  // make TextureAtlas draw calls
  t_atlas.drawImg(gRenderer, TextureId::TILE_GRASS, 0, 0);
  t_atlas.drawImg(gRenderer, TextureId::TILE_GRASS, 32, 32);
  t_atlas.drawImg(gRenderer, TextureId::TILE_GRASS, 64, 0);
  t_atlas.drawImg(gRenderer, TextureId::TILE_GRASS, 96, 32);

  t_atlas.drawImg(gRenderer, TextureId::ITEM_PISTOL, 0, 64);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_PISTOL, 32, 96);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_PISTOL, 64, 128);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_PISTOL, 96, 160);

  t_atlas.drawImg(gRenderer, TextureId::ITEM_BREAD_LOAF, 128, 192);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_BREAD_LOAF, 160, 224);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_BREAD_LOAF, 192, 256);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_BREAD_LOAF, 224, 288);

  t_atlas.drawImg(gRenderer, TextureId::ITEM_CHICKEN_LEG, 200, 200);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_CHICKEN_LEG, 232, 232);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_CHICKEN_LEG, 264, 264);
  t_atlas.drawImg(gRenderer, TextureId::ITEM_CHICKEN_LEG, 296, 296);

  t_atlas.drawImg(gRenderer, TextureId::PLAYER_IDLE_DOWN, 320, 300);
  t_atlas.drawImg(gRenderer, TextureId::PLAYER_IDLE_DOWN, 370, 300);
  t_atlas.drawImg(gRenderer, TextureId::PLAYER_IDLE_DOWN, 320, 400);
  t_atlas.drawImg(gRenderer, TextureId::PLAYER_IDLE_DOWN, 370, 400);

	// render screen
	SDL_RenderPresent(gRenderer);

  // run event loop, waiting for the window to close
  bool quit = false;
  SDL_Event e;

  while (!quit)
  {
    // handle input events on queue
    while (SDL_PollEvent(&e) != 0)
    {
      // handle user closing the window: set quit to true to break the loop
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }

  // close the window, free resources, etc.
  close();
}

bool init()
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO < 0))
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	// create window with SCREEN_WIDTH and SCREEN_HEIGHT
  gWindow = SDL_CreateWindow("Texture Atlas Test", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (gWindow == NULL)
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// create renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	return true;
}

bool loadMedia()
{
	textureAtlasImg = loadTexture("example_texture_atlas.png");

  if (textureAtlasImg == NULL)
  {
    printf("Couldn't load texture atlas\n");
    return false;
  }

  return true;
}

// loads a texture given the relative file path
SDL_Texture* loadTexture(string path)
{
	// load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return NULL;
	}

	SDL_Texture* new_texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (new_texture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	// free loaded surface (no longer necessary), since we're using the SDL_Texture
	SDL_FreeSurface(loadedSurface);

	return new_texture;
}

void close()
{
	SDL_DestroyTexture(textureAtlasImg);

	// destroy renderer
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	// destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// quit SDL subsystems
	IMG_Quit();
  SDL_Quit();
}
