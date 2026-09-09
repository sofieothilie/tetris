#ifndef _IO_
#define _IO_

#include <SDL2/SDL.h>

enum colour {
  BLACK,
  RED,
  GREEN,
  BLUE,
  CYAN,
  MAGENTA,
  YELLOW,
  WHITE,
  COLOUR_MAX
}; // Colours

// ——————————————————————————–
// IO
// ——————————————————————————–

class IO {
private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  int mScreenHeight;

public:
  IO();
  ~IO();

  void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum colour pC);
  void ClearScreen();
  int GetScreenHeight();
  int InitGraph();
  int Pollkey();
  int Getkey();
  int IsKeyDown(int pKey);
  void UpdateScreen();
};

#endif