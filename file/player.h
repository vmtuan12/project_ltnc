#ifndef PLAYER_H
#define PLAYER_H

#include "baseObject.h"
#include "rocket.h"

class player : public baseObject
{
public:
    player();
    ~player();

    void inputKey(SDL_Event e, SDL_Renderer *ren);
    void loadPlayerAmmo(SDL_Renderer *ren);

    void setAmmo(std::vector<rocket*> ammo_) {ammoNum = ammo_;}
    std::vector<rocket*> getAmmo() const {return ammoNum;}

protected:
    int x_val;
    int y_val;
    std::vector<rocket*> ammoNum;
};

#endif
