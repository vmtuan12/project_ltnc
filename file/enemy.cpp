#include "enemy.h"

enemy::enemy()
{
    x_val = 0;
    y_val = 0;

    rect.x = 0;
    rect.y = 0;
    rect.w = enemy_width;
    rect.h = enemy_height;
}

enemy::~enemy()
{
    if(ammoNum.size() > 0){
        for(long long unsigned int i = 0; i < ammoNum.size(); i++){
            rocket *eAmmo = ammoNum.at(i);
            if(eAmmo != NULL) delete eAmmo;
        }
        ammoNum.clear();
    }
}

void enemy::loadEnemy(SDL_Renderer *ren, enemy *ENEMYS)
{
    srand((int)time(0));
    int rand_x;
    for(int i = 0; i < enemy_quantity; i++){
        enemy *p_enemy = ENEMYS + i;

        if(p_enemy != NULL){

            if(i == 0 || i == 3) rand_x = 1 + rand()%(2+1-1);           //need to fix
            if(i == 1 || i == 6) rand_x = 3 + rand()%(4+1-3);
            if(i == 2 || i == 5) rand_x = 5 + rand()%(6+1-5);
            if(i == 4 || i == 7 || i == 8 || i == 9) rand_x = 1 + rand()%6;
            //rand_x = 1 + rand()%6;

            if(i == 0 || i == 1) p_enemy->loadImg("car/enemy_pp.bmp",ren);                    //load enemy
            else if(i == 6) p_enemy->loadImg("car/enemy_yel.bmp",ren);
            else if(i == 2 || i == 3) p_enemy->loadImg("car/enemy_black.bmp",ren);
            else p_enemy->loadImg("car/police.bmp",ren);

            p_enemy->setRect(22 + 90 + (rand_x-1)*90,-rand_x*100);                 //load vi tri xuat phat enemy
            p_enemy->set_y(speed[0]);                                              //speed, max = 8-10

            rocket *enemyAmmo = new rocket();
            p_enemy->loadEnemyAmmo(enemyAmmo,ren);                     //load dan enemy
        }
    }
}

void enemy::movingControl(int const &x_limit, int const &y_limit)
{
    srand((int)time(0));
    rect.y += y_val;

    int rand_x, rand_y1, rand_y2, rand_y3;
    static int temp = 0;
    if(rect.y >= y_limit){                                          //need to fix

        score++;
        std::cout << score << std::endl;

        if(temp == 0 || temp == 3) rand_x = 1 + rand()%(2+1-1);
        else if(temp == 1 || temp == 6) rand_x = 3 + rand()%(4+1-3);
        else if(temp == 2 || temp == 5) rand_x = 5 + rand()%(6+1-5);
        else rand_x = 1 + rand()%6;
        //rand_x = 1 + rand()%6;

        rect.x = 22 + 90 + (rand_x-1)*90;
        /*
        if(temp == 0 || temp == 3) rect.y = -rand_x*100;
        else if(temp == 1 || temp == 6) rect.y = -rand_x*170;
        else if(temp == 2 || temp == 5) rect.y = -rand_x*240;
        else if(temp == 4 || temp == 8) rect.y = -rand_x*310;
        else rect.y = -rand_x*380;

        rand_y1 = 5 + rand()%(10 + 1 - 5);
        rand_y2 = 1 + rand()%(6 + 1 - 1);
        rand_y3 = 1 + rand()%(6 + 1 - 1);
        */
        rect.y = -300;

        //rect.y = -rand_x*200;
        temp++;
        if(temp >= enemy_quantity) temp = (int)(rand()%enemy_quantity);
    }
}

void enemy::input(SDL_Event e)
{

}

void enemy::loadEnemyAmmo(rocket *eAmmo, SDL_Renderer *ren)      //load dan enemy
{
    if(eAmmo != NULL){
        eAmmo->loadImg("item/enemy.bmp",ren);
        eAmmo->add_fired(true);
        eAmmo->setSize(AMMO_WITDH,AMMO_HEIGHT);
        eAmmo->set_y(12);                               //speed rocket
        eAmmo->setRect(rect.x,rect.y + enemy_height);

        ammoNum.push_back(eAmmo);
    }
}

void enemy::enemyFire(const int &x_limit, const int &y_limit, SDL_Renderer *ren)        //enemy ban dan
{
    for(long long unsigned int i = 0; i < ammoNum.size(); i++){
        rocket *eAmmo = ammoNum.at(i);
        if(eAmmo != NULL){
            if(eAmmo->check_fired()){
                eAmmo->show(ren);
                eAmmo->reverseMoving(SCREEN_WIDTH-300,SCREEN_HEIGHT);
            }
            else{
                eAmmo->add_fired(true);                             //doi trang thai fired = true
                eAmmo->setRect(rect.x,rect.y + enemy_height);
            }
        }
    }
}

void enemy::ingameEnemy(enemy *ENEMYS, SDL_Renderer *ren)               //show enemy + di chuyen + ban
{
    for(int j = 0; j < enemy_quantity; j++){
        enemy *p_enemy = ENEMYS + j;

        if(p_enemy != NULL){
            p_enemy->show(ren);
            p_enemy->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);                          //enemy move
            if(j == 7 || j == 5 || j == 4) p_enemy->enemyFire(SCREEN_WIDTH,SCREEN_HEIGHT,ren);      //dan
        }
    }
}

void enemy::changeSpeed(enemy *ENEMYS)
{
    if(score >= 20){
        for(int j = 0; j < enemy_quantity; j++){
            enemy *p_enemy = ENEMYS + j;
            p_enemy->set_y(speed[1]);
        }
    }
    if(score >= 40){
        for(int j = 0; j < enemy_quantity; j++){
            enemy *p_enemy = ENEMYS + j;
            p_enemy->set_y(speed[2]);
        }
    }
    if(score >= 60){
        for(int j = 0; j < enemy_quantity; j++){
            enemy *p_enemy = ENEMYS + j;
            p_enemy->set_y(speed[3]);
        }
    }
    if(score >= 80){
        for(int j = 0; j < enemy_quantity; j++){
            enemy *p_enemy = ENEMYS + j;
            p_enemy->set_y(speed[4]);
        }
    }
}
