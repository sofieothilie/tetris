#include "Game.hpp"
// #ifndef LINUX
// #include <windows.h>
// #endif
#include <iostream>

/**
 * @brief  The application entry point.
 * @retval int
 */

int main(void) {
  // —– Vars —–
  std::string tetris = R"(
    ,----,                 ,----,                               
    ,/   .`|               ,/   .`|                               
  ,`   .'  :   ,---,.    ,`   .'  :,-.----.     ,---,  .--.--.    
;    ;     / ,'  .' |  ;    ;     /\    /  \ ,`--.' | /  /    '.  
.'___,/    ,',---.'   |.'___,/    ,' ;   :    \|   :  :|  :  /`. /  
|    :     | |   |   .'|    :     |  |   | .\ ::   |  ';  |  |--`   
;    |.';  ; :   :  |-,;    |.';  ;  .   : |: ||   :  ||  :  ;_     
`----'  |  | :   |  ;/|`----'  |  |  |   |  \ :'   '  ; \  \    `.  
  '   :  ; |   :   .'    '   :  ;  |   : .  /|   |  |  `----.   \ 
  |   |  ' |   |  |-,    |   |  '  ;   | |  \'   :  ;  __ \  \  | 
  '   :  | '   :  ;/|    '   :  |  |   | ;\  \   |  ' /  /`--'  / 
  ;   |.'  |   |    \    ;   |.'   :   ' | \.'   :  |'--'.     /  
  '---'    |   :   .'    '---'     :   : :-' ;   |.'   `--'---'   
           |   | ,'                |   |.'   '---'                
           `----'                  `---'                          
                                                                  )";
  std::cout << tetris << std::endl;

  // Class for drawing stuff. Uses SDL for the rendering
  IO mIO;
  if (mIO.InitGraph() != 0) {
    return 1;
  }
  int mScreenHeight = mIO.GetScreenHeight();

  // Pieces
  Pieces mPieces;

  // Board
  Board mBoard(&mPieces, mScreenHeight);

  // Game
  Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

  // Get the actual clock milliseconds (SDL)
  unsigned long mTime1 = SDL_GetTicks();
  std::cout << "Initialisation Complete.\n" << std::endl;

  std::cout << "Playing game. wooo<3.\n" << std::endl;
  
  while (!mIO.IsKeyDown(SDLK_ESCAPE)) {

    mIO.ClearScreen();
    mGame.DrawScene();
    mIO.UpdateScreen();

    int mKey = mIO.Pollkey();

    switch (mKey) {
    case SDLK_RIGHT:
    case SDLK_d: // Move piece right
      if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece,
                                    mGame.mRotation)) {
        mGame.mPosX++;
      }
      break;
    case SDLK_LEFT:
    case SDLK_a: // Move piece left
      if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece,
                                    mGame.mRotation)) {
        mGame.mPosX--;
      }
      break;
    case SDLK_DOWN:
    case SDLK_s: // Move piece down
      if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece,
                                    mGame.mRotation)) {
        mGame.mPosY++;
      } else {
        mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                          mGame.mRotation);
        mBoard.DeletePossibleLines();

        if (mBoard.IsGameOver()) {
          mIO.Getkey();
          exit(0);
        }
        mGame.CreateNewPiece();
      }
      break;
      break;
    case SDLK_x:
    case SDLK_SPACE: // Drop piece
      while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece,
                                       mGame.mRotation)) {
        mGame.mPosY++;
      }
      mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                        mGame.mRotation);
      mBoard.DeletePossibleLines();

      if (mBoard.IsGameOver()) {
        mIO.Getkey();
        exit(0);
      }
      mGame.CreateNewPiece();
      break;

    case SDLK_z: case SDLK_UP: case SDLK_w: // Rotate piece
      if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                                    (mGame.mRotation + 1) % 4)) {
        mGame.mRotation = (mGame.mRotation + 1) % 4;
      }
      break;
    }
    // Piece will drop one step due to idle time
    unsigned long mTime2 = SDL_GetTicks();
    if (mTime2 - mTime1 > WAIT_TIME) {
      if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece,
                                    mGame.mRotation)) {
        mGame.mPosY++;
      } else {
        mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                          mGame.mRotation);
        mBoard.DeletePossibleLines();

        if (mBoard.IsGameOver()) {
          mIO.Getkey();
          exit(0);
        }
        mGame.CreateNewPiece();
      }
      mTime1 = SDL_GetTicks();
    }
  }
  std::cout << "Esc pressed. Ended game.\n" << std::endl;
  return 0;
}