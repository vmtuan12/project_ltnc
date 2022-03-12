#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "function.h"

class baseObject
{
public:
    baseObject();
    ~baseObject();
    void show();
    bool loadImg(const std::string  file_name);
    void setRect(int x, int y){
        rect.x = x;
        rect.y = y;
    }
    SDL_Rect getRect(){return rect;}
    //SDL_Texture *getObj(const std::string  file_name);
    SDL_Texture *obj;
    SDL_Rect rect;
//protected:


};

#endif // BASEOBJECT_H

