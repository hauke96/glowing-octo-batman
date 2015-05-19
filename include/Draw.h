#ifndef DRAW_H
#define DRAW_H
#include <string>

class Draw
{
        std::string _titleImage;
    public:
        Draw();
        virtual ~Draw();
        void loadAll();
        void printMainMenuImage();
        void printMainMenuText();
    protected:
    private:
};

#endif // DRAW_H
