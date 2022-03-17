#include "player.h"
#include "baseObject.h"
#include "function.h"
#include "rocket.h"
#include "enemy.h"

using namespace std;

int main(int argc, char* argv[])
{

    func::initSDL(window, renderer);
    bool load_img = imageFunc::load_img_bgr(renderer);
    if(load_img == false){
        imageFunc::del_img_bgr();
        func::quitSDL(window, renderer);
    }

    SDL_RenderClear(renderer);

    player car;
    car.setRect(40,510);
    car.loadImg("car/green.bmp",renderer);                      //load player
    //car.show(renderer);
    //SDL_RenderPresent(renderer);

    srand((int)time(0));
    int rand_x = 1 + rand()%6;
    enemy *p_enemy = new enemy();
    p_enemy->loadImg("car/pp.bmp",renderer);                    //load enemy
    p_enemy->setRect(enemy_x_position[rand_x-1],40);
    p_enemy->set_y(5);

    while(true){
        SDL_Delay(10);

        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
                imageFunc::del_img_bgr();
                func::quitSDL(window,renderer);
                return 0;
            }
            car.inputKey(event,renderer);
        }


        SDL_RenderClear(renderer);
        imageFunc::load_bgr(renderer);
        car.show(renderer);
        //cout << car.rect.x << endl;

        for(long long unsigned int i = 0; i < car.getAmmo().size(); i++){
            //std::cout << car.getAmmo().size() << endl;
            std::vector<rocket*> ammo_quantity = car.getAmmo();
            //cout << ammo_quantity.size() << endl;
            rocket* p_ammo = ammo_quantity.at(i);
            if(p_ammo != NULL){
                if(p_ammo->check_fired()){

                    p_ammo->show(renderer);                       // them ham dan bay
                    p_ammo->moving(0,0);
                    //cout << p_ammo->rect.y << endl;
                    //SDL_RenderPresent(renderer);
                }
                else{
                    if(p_ammo != NULL){
                        ammo_quantity.erase(ammo_quantity.begin() + i);
                        car.setAmmo(ammo_quantity);

                        delete p_ammo;
                        p_ammo = NULL;
                    }
                }
            }

        }

        p_enemy->show(renderer);
        p_enemy->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);


    }

    imageFunc::del_img_bgr();
    //Kết thúc SDL (giải phóng các biển window và renderer)
    func::quitSDL(window, renderer);
    return 0;
}





bool imageFunc::load_img_bgr(SDL_Renderer *ren)
{
    background = imageFunc::loadTexture("bgr/road.bmp", ren);
    control = imageFunc::loadTexture("bgr/control.bmp",ren);

    if (background == nullptr || control == nullptr) return false;

    return true;
}

void imageFunc::del_img_bgr()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(control);
}

void imageFunc::load_bgr(SDL_Renderer *ren)
{
    imageFunc::renderTexture(background, ren, 0, 0, SCREEN_WIDTH-300, SCREEN_HEIGHT);
    imageFunc::renderTexture(control, ren, 900, 0);
}


