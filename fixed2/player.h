#ifndef INHERITED1_H
#define INHERITED1_H

#include "baseObject.h"
#include "rocket.h"

const int OBJ_WIDTH = 70;
const int OBJ_HEIGHT = 120;

class player : public baseObject
{
public:
    player();
    ~player();

    void inputKey(SDL_Event e, SDL_Renderer *ren);

    void setAmmo(std::vector<rocket*> ammo_) {ammoNum = ammo_;}
    std::vector<rocket*> getAmmo() const {return ammoNum;}

protected:
    int x_val;
    int y_val;
    std::vector<rocket*> ammoNum;
};

#endif // INHERITED1_H
