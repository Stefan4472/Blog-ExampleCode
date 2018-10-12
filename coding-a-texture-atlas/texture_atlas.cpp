#include "texture_atlas.h"

// image regions corresponding to int(ItemType)
const SDL_Rect TEXTURE_REGIONS[6] =
{
    SDL_Rect { 0, 0, 0, 0 },  // NONE
    SDL_Rect { 0, 0, 32, 32 },  // TILE_GRASS
    SDL_Rect { 32, 0, 27, 18 },  // ITEM_PISTOL
    SDL_Rect { 32, 20, 19, 15 },  // ITEM_BREAD_LOAF
    SDL_Rect { 32, 37, 25, 14 },  // ITEM_CHICKEN_LEG
    SDL_Rect { 61, 0, 43, 55 }  // PLAYER_IDLE_DOWN
};


TextureAtlas::TextureAtlas(SDL_Texture* atlasImg)
{
  this->atlasImg = atlasImg;
}

int TextureAtlas::getWidth(TextureId textureId)
{
  return TEXTURE_REGIONS[int(textureId)].w;
}

int TextureAtlas::getHeight(TextureId textureId)
{
  return TEXTURE_REGIONS[int(textureId)].h;
}

void TextureAtlas::drawImg(SDL_Renderer* renderer, TextureId textureId, int x, int y)
{
  // convert TextureId into int index
  int texture_index = static_cast<int>(textureId);

  // set destination coordinates: given (x,y) with texture's width and height
  dest.x = x;
	dest.y = y;
	dest.w = TEXTURE_REGIONS[texture_index].w;
	dest.h = TEXTURE_REGIONS[texture_index].h;

	// draw to the renderer with source set to the specified region
	SDL_RenderCopy(renderer, atlasImg, &TEXTURE_REGIONS[texture_index], &dest);
}
