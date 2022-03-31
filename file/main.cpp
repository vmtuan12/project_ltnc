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
        ENEMYS->ingameEnemy(ENEMYS,renderer);           //enemy di chuyen + ban' dan
        p_item->ingameItem(p_item,renderer);


        SDL_RenderPresent(renderer);

    }

    delete []ENEMYS;
    delete []p_item;
    imageFunc::del_img_bgr();
    func::quitSDL(window, renderer);
    return 0;
}


