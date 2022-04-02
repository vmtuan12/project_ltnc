#include "player.h"
#include "baseObject.h"
#include "function.h"
#include "rocket.h"
#include "enemy.h"
#include "side_obj.h"

using namespace std;

int main(int argc, char* argv[])
{

    srand((int)time(0));

    func::initSDL(window, renderer);
    bool load_img = imageFunc::load_img_bgr(renderer);
    if(load_img == false){
        imageFunc::del_img_bgr();
        func::quitSDL(window, renderer);
    }

    SDL_RenderClear(renderer);

    player car;
    car.setRect(22 + 90 + (rand()%6)*90,550);
    car.loadImg("car/green.bmp",renderer);                      //load player

    enemy *ENEMYS = new enemy[enemy_quantity];                          //khoi tao mang enemy va load anh? enemy
    ENEMYS->loadEnemy(renderer,ENEMYS);

    item *p_item = new item[item_quantity];
    p_item->loadItem(renderer,p_item);

    while(true){
        SDL_Delay(10);

        while(SDL_PollEvent(&event)){                                                                           //doi event
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
                imageFunc::del_img_bgr();
                func::quitSDL(window,renderer);
                return 0;
            }
            car.inputKey(event,renderer);
        }

        SDL_RenderClear(renderer);                      //load bgr + car

        imageFunc::load_bgr(renderer);                  //di chuyen man hinh

        car.show(renderer);
        car.loadPlayerAmmo(renderer);                   //load rocket cho player

        ENEMYS->changeSpeed(ENEMYS);
        //ENEMYS->ingameEnemy(ENEMYS,renderer,endGame,enemy_die,car.getRect(),car.getAmmo());           //enemy di chuyen + ban' dan

        for(int j = 0; j < enemy_quantity; j++){
            enemy *p_enemy = ENEMYS + j;
            SDL_Rect enemyRocket_rect;
            if(p_enemy != NULL){
                p_enemy->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);                          //enemy move
                p_enemy->show(renderer);
                if(j == 7 || j == 5 || j == 4) p_enemy->enemyFire(SCREEN_WIDTH,SCREEN_HEIGHT,renderer,enemyRocket_rect);      //dan
            }

            bool rocketed = imageFunc::collision(car.getRect(),enemyRocket_rect);
            bool car_collision = imageFunc::collision(car.getRect(),p_enemy->getRect());
            if(car_collision == true || rocketed == true) endGame = true;

            std::vector<rocket*> p_rocket = car.getAmmo();
            for(int i = 0; i < p_rocket.size(); i++){
                rocket *roc = p_rocket.at(i);
                if(roc != NULL){
                    bool rocket_collision = imageFunc::collision(roc->getRect(),p_enemy->getRect());
                    if(rocket_collision){
                        car.eraseRocket(i);


                    }
                }
            }

        }

        p_item->ingameItem(p_item,renderer);

        SDL_RenderPresent(renderer);


        if(endGame){
            if(MessageBox(NULL,"YOU DIED","ABC",MB_OK) == IDOK){
                delete []ENEMYS;
                delete []p_item;
                imageFunc::del_img_bgr();
                func::quitSDL(window, renderer);
                return 0;
            }
        }

    }

    delete []ENEMYS;
    delete []p_item;
    imageFunc::del_img_bgr();
    func::quitSDL(window, renderer);
    return 0;
}


