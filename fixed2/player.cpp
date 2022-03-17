#include "player.h"
#include "baseObject.h"
#include "function.h"

player::player()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = OBJ_WIDTH;
    rect.h = OBJ_HEIGHT;
    x_val = 0;
    y_val = 0;
}

player::~player()
{
    SDL_DestroyTexture(obj);
}

void player::inputKey(SDL_Event e, SDL_Renderer *ren)
{
    int step = 150;
    if(e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_a){
            step = 150;
            if(rect.x > 150) rect.x = (rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_d){
            step = 150;
            if(rect.x < 750) rect.x = (rect.x + step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_s){
            step = 60;
            if(rect.y != 510) rect.y = (rect.y + step) % SCREEN_HEIGHT;
        }
        if (e.key.keysym.sym == SDLK_w){
            step = 60;
            if(rect.y > 100) rect.y = (rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
        }
        if (e.key.keysym.sym == SDLK_j){
            rocket* pAmmo = new rocket();

            pAmmo->setSize(AMMO_WITDH,AMMO_HEIGHT);
            pAmmo->loadImg("item/rocket.bmp",ren);
            pAmmo->setRect(this->rect.x,this->rect.y - 120);          //giu nguyen toa do x, tru di car.height
            pAmmo->add_fired(true);

            ammoNum.push_back(pAmmo);
        }
    }
    if(e.type == SDL_MOUSEBUTTONDOWN){

    }
}

