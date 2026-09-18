#pragma once

#include <SDL3_image/SDL_image.h>

typedef struct Cen_Texture {
  SDL_Texture *texturePtr;
  int width;
  int height;
} Cen_Texture;

void Cen_DestroyTexture(Cen_Texture *dstTex);
bool Cen_LoadTextureFromFile(const char *path, Cen_Texture **dstTex);
void Cen_RenderTexture(float x, float y, Cen_Texture *dstTex);
