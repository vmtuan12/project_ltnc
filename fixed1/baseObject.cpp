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
bool baseObject::loadImg(const std::string file_name)
{
    obj = imageFunc::loadTexture(file_name,renderer);
    if(obj == NULL) return false;
    return true;
}

void baseObject::show()
{
    if(obj != NULL) imageFunc::renderTexture(obj,renderer,rect.x,rect.y,70,120);
}

