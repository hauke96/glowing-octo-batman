#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <Observer.h>
#include <SubMapViewer_Village.h>
#include <string>

class Draw;
class GameManager;

class MapViewer: public GameScreen, public Observer
{
	int _selectedField;
	char _selectedFieldChar;
	std::string _mapGraphics[5][3];
	SubMapViewer_Village *_subMap;

    public:
        MapViewer(Draw drawer, GameManager *gameManager);
        virtual ~MapViewer();
        void update(std::string input);
        void notified();
    protected:
    private:
        bool executeInput(std::string input);
        void renderImage();
        std::string getRowOf(char field, int row);
        std::string getFieldDescription(char field);
};

#endif // MAPVIEWER_H
