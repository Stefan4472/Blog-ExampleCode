#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <SDL2/SDL.h>
#include <stdexcept>
#include "texture_ids.h"

using namespace std;

/*
Provides access to game graphics via a single "atlas" image. All used graphics
are placed in a single image. Individual images are retrieved by subimaging the
full atlas image with pre-determined, known SDL_Rects.

The TextureId enum, defined in texture_ids.h, provides image identifiers.
The textureRegions array defines the bounds of the corresponding textures in
the atlas.
*/
class TextureAtlas
{
  private:
    // full image
    SDL_Texture* atlasImg;
    // source and destination rects used for making render() calls
    SDL_Rect src, dest;

  public:
    // init with full atlas image
    TextureAtlas(SDL_Texture* atlasImg);

    // returns width (px) of specified Texture image
    int getWidth(TextureId textureId);
    // returns height (px) of specified Texture image
    int getHeight(TextureId textureId);

    // draws image given by textureId to given SDL_Surface at x,y
    void drawImg(SDL_Renderer* renderer, TextureId textureId, int x, int y);
};
#endif
