#include "baseObject.h"
#include "function.h"

baseObject::baseObject()
{
    rect.x = 0;
    rect.y = 0;
    obj = NULL;
}

baseObject::~baseObject()
{
    if(obj != NULL) SDL_DestroyTexture(obj);
}
/*
SDL_Texture baseObject::*getObj(const std::string file_name)
{
    obj = imageFunc::loadTexture(file_name,renderer);
    return obj;
}
*/
void baseObject::loadImg(const std::string file_name, SDL_Renderer *ren)
{
    obj = imageFunc::loadTexture(file_name,ren);
}

void baseObject::show(SDL_Renderer *ren)
{
    if(obj != NULL) imageFunc::renderTexture(obj,ren,rect.x,rect.y,70,120);
}

