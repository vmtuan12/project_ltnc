#ifndef ENEMY_H
#define ENEMY_H

#include "function.h"
#include "baseObject.h"
#include "rocket.h"

int const enemy_width = 45;
int const enemy_height = 70;

class enemy : public baseObject
{
public:
    enemy();
    ~enemy();

    void loadEnemy(SDL_Renderer *ren, enemy *ENEMYS);
    void movingControl(int const &x_limit, int const &y_limit, int &scr);
    void input(SDL_Event e);

    void set_x(const int &val) {x_val = val;}
    void set_y(const int &val) {y_val = val;}
    int get_x() const {return x_val;}
    int get_y() const {return y_val;}

    void setAmmo(std::vector<rocket*> ammo_) {ammoNum = ammo_;}
    std::vector<rocket*> getAmmo() const {return ammoNum;}

    void loadEnemyAmmo(rocket *eAmmo, SDL_Renderer *ren);
    void enemyFire(const int &x_limit, const int &y_limit, SDL_Renderer *ren, SDL_Rect &enemyRocket_rect, int &scr);

    void ingameEnemy(enemy *ENEMYS, SDL_Renderer *ren, bool &die, const SDL_Rect &car,  std::vector<rocket*> ROCKET);
    void changeSpeed(enemy *ENEMYS, int &scr);
    void lockSpeed(enemy *ENEMYS, int &spBgr);
    void enemy_die();
    void eraseRoc();
    void changeRocketSpeed(const int &speed);

protected:
    int x_val;
    int y_val;
    std::vector<rocket*> ammoNum;
};

#endif // ENEMY_H
