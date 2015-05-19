#ifndef MAINMENU_H
#define MAINMENU_H
#include <GameScreen.h>
#include <Draw.h>
#include <string>

class MainMenu: public GameScreen
{
        Draw _drawer;
    public:
        MainMenu(Draw drawer);
        virtual ~MainMenu();
        void update(std::string input);
        void executeInput(std::string input);
    protected:
    private:
};

#endif // MAINMENU_H
