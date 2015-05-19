#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include <string>

class GameScreen
{
    public:
        GameScreen();
        virtual ~GameScreen();
        virtual void update(std::string input) = 0;
    protected:
    private:
};

#endif // GAMESCREEN_H
