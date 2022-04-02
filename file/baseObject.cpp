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

void baseObject::loadImg(const std::string file_name, SDL_Renderer *ren)
{
    obj = imageFunc::loadTexture(file_name,ren);
}

void baseObject::show(SDL_Renderer *ren)                                        //ham` cho car
{
    if(obj != NULL) imageFunc::renderTexture(obj,ren,rect.x,rect.y,OBJ_WIDTH,OBJ_HEIGHT);
}

void baseObject::ammoShow(SDL_Renderer *ren)                                    //ham` cho rocket
{
    if(obj != NULL) imageFunc::renderTexture(obj,ren,rect.x,rect.y,AMMO_WITDH,AMMO_HEIGHT);
}

void baseObject::itemShow(SDL_Renderer *ren)                                    //ham` cho item
{
    if(obj != NULL) imageFunc::renderTexture(obj,ren,rect.x,rect.y,itemW,itemH);
}
