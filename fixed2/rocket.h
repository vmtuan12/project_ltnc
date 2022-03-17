#ifndef ROCKET_H
#define ROCKET_H

#include "baseObject.h"

const int AMMO_WITDH = 70;
const int AMMO_HEIGHT = 70;

class rocket : public baseObject
{
public:
    rocket();
    ~rocket();
    void inputKey(SDL_Event e);
    void moving(const int &x_limit, const int &y_limit);

    void add_fired(bool fired_) {fired = fired_;}
    bool check_fired() const {return fired;}
    void setSize(const int &w,const int &h){
        rect.w = w;
        rect.h = h;
    }

protected:
    int x_val;
    int y_val;
    bool fired;
};

#endif // ROCKET_H
