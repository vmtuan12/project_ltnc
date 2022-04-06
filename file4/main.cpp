#include "player.h"
#include "baseObject.h"
#include "function.h"
#include "rocket.h"
#include "enemy.h"
#include "side_obj.h"
#include "timer.h"

using namespace std;

int main(int argc, char* argv[])
{
    timer fps_timer;
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
        fps_timer.start();
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

        Uint32 time = SDL_GetTicks()/1000;
        string time_val = to_string(time);
        //cout << time_val << endl;

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
                        p_enemy->setRect(22 + 90 + (rand()%6)*90,-500);
                        //p_enemy->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);
                        break;
                    }
                }
                //
                p_enemy->show(renderer);
                if(j == 7 || j == 5 || j == 4) p_enemy->enemyFire(SCREEN_WIDTH,SCREEN_HEIGHT,renderer,enemyRocket_rect);      //dan
            }

            bool rocketed = imageFunc::collision(car.getRect(),enemyRocket_rect);               //dinh dan
            bool car_collision = imageFunc::collision(car.getRect(),p_enemy->getRect());        //dam xe
            if(car_collision){                          //fix rocket

                if(armor == 0) endGame = true;                    //va cham = endgame
                p_enemy->enemy_die();
            }
            if(rocketed) endGame = true;

            std::vector<rocket*> p_rocket = car.getAmmo();
            for(int i = 0; i < p_rocket.size(); i++){
                rocket *roc = p_rocket.at(i);
                if(roc != NULL){
                    bool rocket_collision = imageFunc::collision(roc->getRect(),p_enemy->getRect());        //ban trung
                    //bool roc_vs_roc = imageFunc::collision(roc->getRect(),enemyRocket_rect);                //2 rocket va cham
                    if(rocket_collision){
                        car.eraseRocket(i);
                        p_enemy->enemy_die();
                    }
                    /*if(roc_vs_roc){
                        p_enemy->eraseRoc();
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
                if(it == 4){
                    car.changeCar(imageFunc::loadTexture("car/black.bmp",renderer));                //fixing
                    armor += 1;
                }
            }
        }
        if(armor > 0){
            if(time_val != s) armTime.push_back(time_val);
            s = time_val;
            cout << time_val << endl;
            if(armTime.size() == armor*4){
                car.changeCar(imageFunc::loadTexture("car/green.bmp",renderer));
                armor = 0;
                armTime.clear();
            }
        }

        SDL_RenderPresent(renderer);
        int real_time = fps_timer.get_tick();
        int time_one_frame = 1000/fps;
        if(real_time < time_one_frame){
            int delay_time = time_one_frame - real_time;
            if(delay_time >= 0) SDL_Delay(delay_time);
        }

        if(endGame == true){
            if(MessageBox(NULL,"YOU DIED","Message",MB_OK) == IDOK){
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


