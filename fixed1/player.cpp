#include "player.h"
#include "baseObject.h"
#include "function.h"

player::player()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = OBJ_WIDTH;
    rect.h = OBJ_HEIGHT;
    x_val = 0;
    y_val = 0;
}

player::~player()
{
    SDL_DestroyTexture(obj);
}



