#include "MainWindow.hpp"
#include <QApplication>
#include <iostream>

/**
 * @brief  The application entry point.
 * @retval int
 */

int main(int argc, char *argv[]) {
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

  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}