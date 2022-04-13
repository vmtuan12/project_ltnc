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

void player::inputKey(SDL_Event e, SDL_Renderer *ren, int &roc_quan, Mix_Chunk *roc_sound, Mix_Music *gMusic)
{
    int step = 90;
    if(e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_a){
            step = 90;
            if(rect.x > 180) rect.x = (rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_d){
            step = 90;
            if(rect.x < 540) rect.x = (rect.x + step) % SCREEN_WIDTH;
        }
        if (e.key.keysym.sym == SDLK_s){
            step = 30;
            if(rect.y != 550) rect.y = (rect.y + step) % SCREEN_HEIGHT;
        }
        if (e.key.keysym.sym == SDLK_w){
            step = 30;
            if(rect.y >= 340) rect.y = (rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
        }
        if (e.key.keysym.sym == SDLK_j){
            if(roc_quan > 0){
                //std::cout << roc_quan << std::endl;
                rocket* pAmmo = new rocket();

                pAmmo->setSize(AMMO_WITDH,AMMO_HEIGHT);
                pAmmo->loadImg("item/rocket.bmp",ren);
                pAmmo->setRect(this->rect.x,this->rect.y - OBJ_HEIGHT);
                pAmmo->set_y(14);
                pAmmo->add_fired(true);

                ammoNum.push_back(pAmmo);
                Mix_PlayChannel(-1,roc_sound,0);
                roc_quan--;
            }
        }
        if (e.key.keysym.sym == SDLK_p){
            if(Mix_PlayingMusic() == 0) Mix_PlayMusic(gMusic,-1);
            else{
                //If the music is paused
                if( Mix_PausedMusic() == 1 ){
                //Resume the music
                    Mix_ResumeMusic();
                }
                //If the music is playing
                else{
                    //Pause the music
                    Mix_PauseMusic();
                }
            }
        }
        if (e.key.keysym.sym == SDLK_0) Mix_HaltMusic();
    }
}

void player::loadPlayerAmmo(SDL_Renderer *ren)
{
    for(long long unsigned int i = 0; i < ammoNum.size(); i++){

        rocket* p_ammo = ammoNum.at(i);
        if(p_ammo != NULL){
            if(p_ammo->check_fired()){                          //check trang thai fired

                p_ammo->show(ren);
                p_ammo->moving(0,-200);
            }
            else{
                if(p_ammo != NULL){
                    ammoNum.erase(ammoNum.begin() + i);

                    delete p_ammo;
                    p_ammo = NULL;
                }
            }
        }
    }
}

void player::eraseRocket(const int &pos)
{
    if(ammoNum.size() > 0 && 0 <= pos && pos < ammoNum.size()){
        //rocket *p_rocket = ammoNum.at(pos);

        ammoNum.erase(ammoNum.begin() + pos);
        /*
        if(p_rocket != NULL){
            delete p_rocket;
            p_rocket = NULL;
        }*/
    }
}



