#ifndef SUBMAPVIEWER_VILLAGE_H
#define SUBMAPVIEWER_VILLAGE_H
#include <GameManager.h>
#include <Draw.h>

class SubMapViewer_Village: public GameScreen
{
    public:
        SubMapViewer_Village(Draw drawer, GameManager *gameManager);
        virtual ~SubMapViewer_Village();
        void update(std::string input);
    protected:
    private:
        bool executeInput(std::string input);
};

#endif // SUBMAPVIEWER_VILLAGE_H
