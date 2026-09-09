#include "IO.hpp"

namespace {
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

SDL_Color GetColour(colour pColour) {
  switch (pColour) {
  case RED:
    return {255, 0, 0, 255};
  case GREEN:
    return {0, 255, 0, 255};
  case BLUE:
    return {0, 0, 255, 255};
  case CYAN:
    return {0, 255, 255, 255};
  case MAGENTA:
    return {255, 0, 255, 255};
  case YELLOW:
    return {255, 255, 0, 255};
  case WHITE:
    return {255, 255, 255, 255};
  case BLACK:
  default:
    return {0, 0, 0, 255};
  }
}
} // namespace

IO::IO() : mWindow(nullptr), mRenderer(nullptr), mScreenHeight(0) {}

IO::~IO() {
  if (mRenderer != nullptr) {
    SDL_DestroyRenderer(mRenderer);
  }

  if (mWindow != nullptr) {
    SDL_DestroyWindow(mWindow);
  }

  SDL_Quit();
}

/*
======================================
Draws a rectangle

Parameters:

>> pX1 and pX2: Horizontal range of pixels to draw
>> pY1 and pY2: Vertical range of pixels to draw
>> pC: Colour to draw in
======================================
*/
void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum colour pC) {
  SDL_Color colourValue = GetColour(pC);

  SDL_SetRenderDrawColor(mRenderer, colourValue.r, colourValue.g, colourValue.b,
                         colourValue.a);

  SDL_Rect rectangle{
      pX1,
      pY1,
      pX2 - pX1 + 1,
      pY2 - pY1 + 1,
  };

  SDL_RenderFillRect(mRenderer, &rectangle);
}

/*
 ======================================
 Clears the screen
 ======================================
 */
void IO::ClearScreen() {
  SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
  SDL_RenderClear(mRenderer);
}

/*
 ======================================
 Returns the screen height in pixels
 ======================================
 */
int IO::GetScreenHeight() { return mScreenHeight; }

/*
 ======================================
 Initialises the graphics system

 Returns 0 if the graphics system was initialised successfully
 ======================================
 */
int IO::InitGraph() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return 1;
  }

  mWindow =
      SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (mWindow == nullptr) {
    SDL_Quit();
    return 1;
  }

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

  if (mRenderer == nullptr) {
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
    SDL_Quit();
    return 1;
  }

  mScreenHeight = SCREEN_HEIGHT;
  return 0;
}

/*
 ======================================
 Polls for a keyboard event

 Returns the key that was pressed, or 0 if no key was pressed
 ======================================
 */
int IO::Pollkey() {
  SDL_Event event;

  if (SDL_PollEvent(&event) == 0) {
    return 0;
  }

  if (event.type == SDL_QUIT) {
    return SDLK_ESCAPE;
  }

  if (event.type == SDL_KEYDOWN) {
    return event.key.keysym.sym;
  }

  return 0;
}
/*
 ======================================
 Returns the next keyboard input
 ======================================
 */
int IO::Getkey() {
  SDL_Event event;

  while (SDL_WaitEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      return SDLK_ESCAPE;
    }

    if (event.type == SDL_KEYDOWN) {
      return event.key.keysym.sym;
    }
  }

  return 0;
}

/*
 ======================================
 Checks whether a key is currently pressed

 Parameters:

 >> pKey: Key to check

 Returns 1 if the key is pressed, 0 otherwise
 ======================================
 */
int IO::IsKeyDown(int pKey) {
  const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);
  SDL_Scancode scanCode = SDL_GetScancodeFromKey(pKey);

  return keyboardState[scanCode] != 0;
}

/*
 ======================================
 Updates the screen with the current drawing buffer
 ======================================
 */
void IO::UpdateScreen() { SDL_RenderPresent(mRenderer); }