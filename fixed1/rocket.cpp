#include "rocket.h"

rocket::rocket()
{
    rect.x = 0;
    rect.y = 0;
    x_val = 0;
    y_val = 0;
    fired = false;
}

rocket::~rocket()
{

}

void rocket::inputKey(SDL_Event e)
{

}

void rocket::moving(const int &x_limit, const int &y_limit)
{
    rect.y -= 60;
    if(rect.y < y_limit) fired = false;
}



