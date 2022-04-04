#ifndef ROCKET_H
#define ROCKET_H

#include "baseObject.h"

class rocket : public baseObject
{
public:
    rocket();
    ~rocket();
    void inputKey(SDL_Event e);
    void moving(const int &x_limit, const int &y_limit);
    void reverseMoving(const int &x_limit, const int &y_limit);

    void add_fired(bool fired_) {fired = fired_;}
    bool check_fired() const {return fired;}
    void setSize(const int &w,const int &h){
        rect.w = w;
        rect.h = h;
    }

    void set_x(const int &x) {x_val = x;}
    void set_y(const int &y) {y_val = y;}
    int get_x() const {return x_val;}
    int get_y() const {return y_val;}

protected:
    int x_val;
    int y_val;
    bool fired;
};

#endif // ROCKET_H
