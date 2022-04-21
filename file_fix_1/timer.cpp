#include "timer.h"

timer::timer()
{
    start_tick = 0;
    pause_tick = 0;
    is_start = false;
    is_pause = false;
}

timer::~timer()
{

}

void timer::start()
{
    is_start = true;
    is_pause = false;
    start_tick = SDL_GetTicks();

}

void timer::stop()
{
    is_pause = false;
    is_start = false;
}

void timer::pause()
{
    if(is_start == true || is_pause == false){
        is_pause = true;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}

void timer::resume()
{
    if(is_pause){
        is_pause = false;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}

int timer::get_tick()
{
    if(is_start){
        if(is_pause) return pause_tick;
        else return SDL_GetTicks() - start_tick;
    }

    return 0;
}
