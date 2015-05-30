#ifndef MAPVIEWER_H
#define MAPVIEWER_H
#include <GameScreen.h>
#include <string>
#include <Draw.h>

class MapViewer: public GameScreen
{
    public:
        MapViewer(Draw drawer, GameManager *gameManager);
        virtual ~MapViewer();
        void update(std::string input);
    protected:
    private:
        bool executeInput(std::string input);
};

#endif // MAPVIEWER_H
