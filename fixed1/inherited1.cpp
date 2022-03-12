#include "inherited1.h"
#include "baseObject.h"
#include "function.h"

inherited1::inherited1()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = OBJ_WIDTH;
    rect.h = OBJ_HEIGHT;
    x_val = 0;
    y_val = 0;
}

inherited1::~inherited1()
{

}

void inherited1::inputKey(SDL_Event e)
{
    int step = 125;
    if(e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_LEFT){
            step = 125;
            rect.x = (rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_RIGHT){
            step = 125;
            rect.x= (rect.x + step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_DOWN){
            step = 60;
            rect.y = (rect.y + step) % SCREEN_HEIGHT;
        }
        if (e.key.keysym.sym == SDLK_UP){
            step = 60;
            rect.y = (rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
        }
    }
}

