#include "texture.h"

#include <stdlib.h>

extern SDL_Renderer *gRendererPtr;

void Cen_DestroyTexture(Cen_Texture *dstTex) {
  SDL_DestroyTexture(dstTex->texturePtr);
  dstTex->texturePtr = NULL;
  dstTex->height = 0;
  dstTex->width = 0;
}

bool Cen_LoadTextureFromFile(const char *path, Cen_Texture **dstTex) {
  // Clean up texture if it already exists
  Cen_DestroyTexture(*dstTex);

  // Load surface
  bool success = false;
  SDL_Surface *loadedSurface = NULL;
  Cen_Texture *newTex = NULL;

  loadedSurface = IMG_Load(path);
  if (loadedSurface == NULL) {
    SDL_Log("Unable to load image %s! SDL_image error: %s\n", path,
            SDL_GetError());
    goto cleanup;
  }

  newTex = malloc(sizeof(Cen_Texture));
  if (newTex == NULL) {
    SDL_Log("Failed to malloc in CenTextureLoadFromFile\n");
    goto cleanup;
  }

  // Create texture from surface
  newTex->texturePtr =
      SDL_CreateTextureFromSurface(gRendererPtr, loadedSurface);
  if (newTex->texturePtr == NULL) {
    SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n",
            SDL_GetError());
    goto cleanup;
  }

  // Get image dimensions
  newTex->width = loadedSurface->w;
  newTex->height = loadedSurface->h;

  *dstTex = newTex;
  success = true;

cleanup:
  if (loadedSurface != NULL) {
    // Clean up loaded surface
    SDL_DestroySurface(loadedSurface);
  }
  if (newTex != NULL && success == false) {
    free(newTex);
    newTex = NULL;
  }

  return success;
}

void Cen_RenderTexture(float x, float y, Cen_Texture *dstTex) {
  // Set texture position
  SDL_FRect dstRect = {x, y, (float)(dstTex->width), (float)(dstTex->height)};

  // Render texture
  SDL_RenderTexture(gRendererPtr, dstTex->texturePtr, NULL, &dstRect);
}
