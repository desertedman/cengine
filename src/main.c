#include "headers.h"
#include "texture.h"

#include <stdbool.h>
#include <stdlib.h>

#define kScreenWidth 640
#define kScreenHeight 480

/* Function Prototypes */
bool Cen_Init();  // Starts up SDL and creates window
bool LoadMedia(); // Loads mediia
void Cen_Close(); // Frees media and shuts down SDL

/* Global Variables */
SDL_Window *gWindowPtr = NULL;     // Window to render to
SDL_Renderer *gRendererPtr = NULL; // Renderer used to draw window
Cen_Texture *gPngTexturePtr;       // Png image we will render

int main(int argc, char *argv[]) {
  int exitCode = 0;

  // Initialize gPngTexture
  gPngTexturePtr = malloc(sizeof(Cen_Texture));
  gPngTexturePtr->texturePtr = NULL;
  gPngTexturePtr->height = 0;
  gPngTexturePtr->width = 0;

  if (Cen_Init() == false) {
    SDL_Log("Unable to initialize program!\n");
    exitCode = 1;
  }

  else {
    if (LoadMedia() == false) {
      SDL_Log("Unable to load media!\n");
      exitCode = 2;
    }

    else {
      bool quit = false;

      SDL_Event e;
      SDL_zero(e);

      while (quit == false) {
        // Get event data
        while (SDL_PollEvent(&e) == true) {
          if (e.type == SDL_EVENT_QUIT) {
            quit = true;
          }
        }

        // Fill background white
        SDL_SetRenderDrawColor(gRendererPtr, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRendererPtr);

        // Render image on screen
        Cen_RenderTexture(0.f, 0.f, gPngTexturePtr);

        // Update screen
        SDL_RenderPresent(gRendererPtr);
      }
    }
  }

  Cen_Close();
  return exitCode;
}

/* Function Implementations */
bool Cen_Init() {
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    success = false;
  }

  else {
    // Create window with renderer
    if (SDL_CreateWindowAndRenderer("SDL3", kScreenWidth, kScreenHeight, 0,
                                    &gWindowPtr, &gRendererPtr) == false) {
      SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
      success = false;
    }
  }

  return success;
}

bool LoadMedia() {
  // File loading flag
  bool success = true;

  // Load splash image
  const char *imagePath =
      "./resources/textures/02-textures-and-extension-libraries\\loaded.png\0";

  if (Cen_LoadTextureFromFile(imagePath, &gPngTexturePtr) == false) {
    SDL_Log("Unable to load png image!\n");
    success = false;
  }

  return success;
}

void Cen_Close() {
  Cen_DestroyTexture(gPngTexturePtr);

  // Destroy window
  SDL_DestroyRenderer(gRendererPtr);
  gRendererPtr = NULL;
  SDL_DestroyWindow(gWindowPtr);
  gWindowPtr = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}
