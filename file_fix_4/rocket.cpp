#include "rocket.h"

rocket::rocket()
{
    rect.x = -100;
    rect.y = -100;
    rect.w = AMMO_WITDH;
    rect.h = AMMO_HEIGHT;
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

void rocket::moving(const int &x_limit, const int &y_limit)                 //dan player
{
    rect.y -= y_val;
    if(rect.y < y_limit) fired = false;
    else fired = true;
}

void rocket::reverseMoving(const int &x_limit, const int &y_limit)          //dan enemy
{
    rect.y += y_val;
    if(rect.y > y_limit) fired = false;
    else fired = true;
}



