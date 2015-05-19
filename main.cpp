#include <iostream>
#include <GameScreen.h>
#include <Draw.h>
#include <MainMenu.h>

using namespace std;

void update(string input);
string readLine();

GameScreen *_gameScreen;
Draw _drawer;

int main()
{
    _drawer.loadAll();
    _gameScreen = new MainMenu(_drawer);
    string input = "";
    input = readLine();

    while(input != "exit")
    {
        update(input);
        input = readLine();
    }
    return 0;
}

void update(string input)
{
    _gameScreen->update(input);
}

string readLine()
{
    string str;
    cout << endl << "~$> ";
    cin >> str;
    return str;
}
