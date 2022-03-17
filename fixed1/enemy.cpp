#include "enemy.h"

enemy::enemy()
{
    x_val = 0;
    y_val = 0;

    rect.x = 0;
    rect.y = 0;
    rect.w = enemy_width;
    rect.h = enemy_height;
}

enemy::~enemy()
{

}

void enemy::movingControl(int const x_limit, int const y_limit)
{
    rect.y += y_val;
    if(rect.y >= y_limit) rect.y = 0;
}

void enemy::input(SDL_Event e)
{

}
