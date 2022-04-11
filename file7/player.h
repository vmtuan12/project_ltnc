#ifndef PLAYER_H
#define PLAYER_H

#include "baseObject.h"
#include "rocket.h"

class player : public baseObject
{
public:
    player();
    ~player();

    void inputKey(SDL_Event e, SDL_Renderer *ren, int &roc_quan);
    void loadPlayerAmmo(SDL_Renderer *ren);
    void changeCar(SDL_Texture *newCar){obj = newCar;}

    void setAmmo(std::vector<rocket*> ammo_) {ammoNum = ammo_;}
    std::vector<rocket*> getAmmo() const {return ammoNum;}
    void eraseRocket(const int &pos);

protected:
    int x_val;
    int y_val;
    std::vector<rocket*> ammoNum;
};

#endif
