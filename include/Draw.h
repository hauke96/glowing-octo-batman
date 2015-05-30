#ifndef DRAW_H
#define DRAW_H
#include <string>

class Draw
{
        std::string _titleImage,
            _map_raw,
            _map_processed;


    public:
        Draw();
        virtual ~Draw();
        void loadAll();
        void printMainMenuImage();
        void printMainMenuText();
        std::string getRawMap();
    protected:
    private:
};

#endif // DRAW_H
