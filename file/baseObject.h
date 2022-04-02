#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "function.h"

const int OBJ_WIDTH = 45;
const int OBJ_HEIGHT = 70;                          //car size

const int AMMO_WITDH = 45;
const int AMMO_HEIGHT = 45;                         //rocket size

const int itemW = 45;
const int itemH = 45;

class baseObject
{
public:
    baseObject();
    ~baseObject();
    void show(SDL_Renderer *ren);
    void ammoShow(SDL_Renderer *ren);
    void itemShow(SDL_Renderer *ren);

    void loadImg(const std::string file_name, SDL_Renderer *ren);
    void setRect(const int &x, const int &y){
        rect.x = x;
        rect.y = y;
    }
    SDL_Rect getRect(){return rect;}

    SDL_Rect rect;
protected:
    SDL_Texture *obj;
    //SDL_Rect rect;

};

#endif // BASEOBJECT_H

