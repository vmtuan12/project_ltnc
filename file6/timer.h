#ifndef TIMER_H
#define TIMER_H

#include "function.h"

class timer
{
public:
    timer();
    ~timer();

    void start();
    void stop();
    void pause();
    void resume();

    int get_tick();

    bool get_start() {return is_start;}
    bool get_pause() {return is_pause;}

private:
    int start_tick;
    int pause_tick;

    bool is_pause;
    bool is_start;

};

#endif // TIMER_H
