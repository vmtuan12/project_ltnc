#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "function.h"

class baseObject
{
public:
    baseObject();
    ~baseObject();
    void show(SDL_Renderer *ren);
    void loadImg(const std::string file_name, SDL_Renderer *ren);
    void setRect(const int &x,const int &y){
        rect.x = x;
        rect.y = y;
    }
    SDL_Rect getRect(){return rect;}
    //SDL_Texture *getObj(const std::string  file_name);
protected:
    SDL_Texture *obj;
    SDL_Rect rect;

};

#endif // BASEOBJECT_H

