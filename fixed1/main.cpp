#include "player.h"
#include "baseObject.h"
#include "function.h"
#include "rocket.h"

using namespace std;

int main(int argc, char* argv[])
{

    func::initSDL(window, renderer);
    bool load_img = imageFunc::load_img(renderer);
    if(load_img == false){
        imageFunc::del_img();
        func::quitSDL(window, renderer);
    }

    SDL_RenderClear(renderer);
    //imageFunc::load_bgr(renderer);

    player car;
    car.setRect(27,510);
    car.loadImg("car/green.bmp",renderer);
    //car.show(renderer);
    //SDL_RenderPresent(renderer);

    enemy *p_enemy = new enemy();
    p_enemy->loadImg("car/pp.bmp",renderer);
    p_enemy->setRect(27,40);

    while(true){
        SDL_Delay(10);

        if ( SDL_WaitEvent(&event) == 0) continue;

        if (event.type == SDL_QUIT) break;
        if(event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_ESCAPE) break;
        car.inputKey(event);

        SDL_RenderClear(renderer);
        imageFunc::load_bgr(renderer);
        car.show(renderer);


        for(int i = 0; i < car.getAmmo().size(); i++){
            //std::cout << car.getAmmo().size() << endl;
            std::vector<rocket*> ammo_quantity = car.getAmmo();
            cout << ammo_quantity.size() << endl;
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

    imageFunc::del_img();
    //Kết thúc SDL (giải phóng các biển window và renderer)
    func::quitSDL(window, renderer);
    return 0;
}





bool imageFunc::load_img(SDL_Renderer *ren)
{
    background = imageFunc::loadTexture("bgr/road2.bmp", ren);
    control = imageFunc::loadTexture("bgr/control.bmp",ren);

    if (background == nullptr || control == nullptr) return false;

    return true;
}

void imageFunc::del_img()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(control);
}

void imageFunc::load_bgr(SDL_Renderer *ren)
{
    imageFunc::renderTexture(background, ren, 0, 0, SCREEN_WIDTH-300, SCREEN_HEIGHT);
    imageFunc::renderTexture(control, ren, 500, 0);
}

void player::inputKey(SDL_Event e)
{
    int step = 125;
    if(e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_a){
            step = 125;
            if(rect.x > 125) rect.x = (rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_d){
            step = 125;
            if(rect.x < 375) rect.x = (rect.x + step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_s){
            step = 10;
            if(rect.y != 510) rect.y = (rect.y + step) % SCREEN_HEIGHT;
        }
        if (e.key.keysym.sym == SDLK_w){
            step = 10;
            if(rect.y > 100) rect.y = (rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
        }

    }
    if(e.type == SDL_MOUSEBUTTONDOWN){
        rocket* pAmmo = new rocket();

        pAmmo->setSize(AMMO_WITDH,AMMO_HEIGHT);
        pAmmo->loadImg("item/rocket.bmp",renderer);
        pAmmo->setRect(this->rect.x,this->rect.y - 120);
        pAmmo->add_fired(true);

        ammoNum.push_back(pAmmo);
    }
}
