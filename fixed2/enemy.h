#ifndef ENEMY_H
#define ENEMY_H

#include "function.h"
#include "baseObject.h"

int const enemy_width = 70;
int const enemy_height = 120;

class enemy : public baseObject
{
public:
    enemy();
    ~enemy();

    void movingControl(int const x_limit, int const y_limit);
    void input(SDL_Event e);

    void set_x(const int val) {x_val = val;}
    void set_y(const int val) {y_val = val;}
    int get_x() const {return x_val;}
    int get_y() const {return y_val;}

protected:
    int x_val;
    int y_val;
};

#endif // ENEMY_H
