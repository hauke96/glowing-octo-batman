#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include <string>
#include <Draw.h>
#include <GameManager.h>

class GameManager;
class GameScreen
{
    public:
        GameScreen(GameManager gameManager);
        virtual ~GameScreen();
        virtual void update(std::string input) = 0;
        Draw _drawer;
    protected:
        GameManager *_gameManager;
    private:
        virtual bool executeInput(std::string input) = 0;
};

#endif // GAMESCREEN_H
