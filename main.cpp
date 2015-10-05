#include <GameManager.h>
#include <iostream>
#include <string>

using namespace std;

// UNDERLINE  : \033[4m
// BOLD       : \033[1m
// NOTHING    : \033[0m

// ROT        : \033[31m
// DARK GREEN : \033[32m
// BROWN      : \033[33m
// BLUE       : \033[34m
// LIGHT GREEN: \033[36m
// GRAY       : \033[37m

int main()
{

    GameManager _gameManager;
    _gameManager.start();
	std::string v;
	std::cin >> v;
    return 0;
}
