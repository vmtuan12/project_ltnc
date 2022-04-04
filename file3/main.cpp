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
    //int posEnemyRoc = 0;

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
            car.inputKey(event,renderer,rocket_quantity);
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
                //
                for(int jj = 0; jj < j; jj++){                                  //check enemy trung` vi tri
                    enemy *pp_enemy = ENEMYS + jj;
                    bool enemy_col = imageFunc::collision(p_enemy->getRect(),pp_enemy->getRect());
                    if(enemy_col){
                        p_enemy->rect.y = -500;
                        //p_enemy->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);
                        break;
                    }
                }
                //
                p_enemy->show(renderer);
                if(j == 7 || j == 5 || j == 4) p_enemy->enemyFire(SCREEN_WIDTH,SCREEN_HEIGHT,renderer,enemyRocket_rect);      //dan
            }

            bool rocketed = imageFunc::collision(car.getRect(),enemyRocket_rect);
            bool car_collision = imageFunc::collision(car.getRect(),p_enemy->getRect());
            //if(car_collision == true || rocketed == true) endGame = true;                    //va cham = endgame

            std::vector<rocket*> p_rocket = car.getAmmo();
            for(int i = 0; i < p_rocket.size(); i++){
                rocket *roc = p_rocket.at(i);
                if(roc != NULL){
                    bool rocket_collision = imageFunc::collision(roc->getRect(),p_enemy->getRect());
                    //bool roc_vs_roc = imageFunc::collision(roc->getRect(),enemyRocket_rect);
                    if(rocket_collision){
                        car.eraseRocket(i);
                        p_enemy->enemy_die();
                    }
                    /*if(roc_vs_roc){
                        p_enemy->eraseRocket(posEnemyRoc);
                        car.eraseRocket(i);
                    }*/
                }
            }

        }

        for(int it = 0; it < item_quantity; it++){
            item *single_item = p_item + it;

            if(single_item != NULL){
                single_item->itemShow(renderer);
                single_item->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);
                for(int itit = 0; itit < it; itit++){                       //check item trung` vi tri
                    item *single_itemmmm = p_item + itit;
                    bool item_col = imageFunc::collision(single_item->getRect(),single_itemmmm->getRect());
                    if(item_col){
                        single_item->rect.y -= 150;
                        break;
                    }
                }
            }
            bool pickItem = imageFunc::collision(car.getRect(),single_item->getRect());
            if(pickItem){
                single_item->picked(it,rocket_quantity,score);
            }
        }

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


