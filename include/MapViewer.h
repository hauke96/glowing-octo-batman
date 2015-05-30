#ifndef MAPVIEWER_H
#define MAPVIEWER_H
#include <GameScreen.h>
#include <string>
#include <Draw.h>

class MapViewer: public GameScreen
{
        int _selectedField;
        char _selectedFieldChar;
        std::string _mapGraphics[5][3];

    public:
        MapViewer(Draw drawer, GameManager *gameManager);
        virtual ~MapViewer();
        void update(std::string input);
    protected:
    private:
        bool executeInput(std::string input);
        void renderImage();
        std::string getRowOf(char field, int row);
        std::string getFieldDescription(char field);
};

#endif // MAPVIEWER_H
