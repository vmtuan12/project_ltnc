#ifndef ENEMY_H
#define ENEMY_H

#include "function.h"
#include "baseObject.h"
#include "rocket.h"
#include "player.h"

int const enemy_width = 45;
int const enemy_height = 70;

class enemy : public baseObject
{
public:
    enemy();
    ~enemy();

    void loadEnemy(SDL_Renderer *ren, enemy *ENEMYS);
    void movingControl(int const &x_limit, int const &y_limit);
    void input(SDL_Event e);

    void set_x(const int &val) {x_val = val;}
    void set_y(const int &val) {y_val = val;}
    int get_x() const {return x_val;}
    int get_y() const {return y_val;}

    void setAmmo(std::vector<rocket*> ammo_) {ammoNum = ammo_;}
    std::vector<rocket*> getAmmo() const {return ammoNum;}

    void loadEnemyAmmo(rocket *eAmmo, SDL_Renderer *ren);
    void enemyFire(const int &x_limit, const int &y_limit, SDL_Renderer *ren, SDL_Rect &enemyRocket_rect);

    void ingameEnemy(enemy *ENEMYS, SDL_Renderer *ren, bool &die, const SDL_Rect &car,  std::vector<rocket*> ROCKET);
    void changeSpeed(enemy *ENEMYS);
    void enemy_die(enemy *ENEMY, const int &pos);

protected:
    int x_val;
    int y_val;
    std::vector<rocket*> ammoNum;
};

#endif // ENEMY_H
