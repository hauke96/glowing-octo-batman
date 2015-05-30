#include <iostream>
#include <GameManager.h>
#include <Draw.h>
#include <MainMenu.h>

using namespace std;

int main()
{
    /*cout << "┌─────┐\n│  ⌂  │\n│ ↟⤊⌂ │\n│ ⌂⌂  │\n└─────┘" << endl;
    cout << "┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐" << endl;
    cout << "│\n│\n│" << endl;
    cout << "├\n│\n│\n│" << endl;
    cout << "├\n│\n│\n│" << endl;
    cout << "├\n│\n│\n│" << endl;
    cout << "├\n│\n│\n│" << endl;
    cout << "├\n│\n│\n│" << endl;
    cout << "├\n│\n│\n│\n└" << endl;*///Just for texting
    GameManager _gameManager;
    _gameManager.start();
    return 0;
}
