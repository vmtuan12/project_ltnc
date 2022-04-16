#include "player.h"
#include "baseObject.h"
#include "function.h"
#include "rocket.h"
#include "enemy.h"
#include "side_obj.h"
#include "timer.h"
#include "explosion.h"
#include "text.h"

using namespace std;

int main(int argc, char* argv[])
{
    timer fps_timer;
    srand((int)time(0));

    func::initSDL(window, renderer);
    bool load_img = imageFunc::load_img_bgr(renderer);
    if(load_img == false){
        func::freeObj();
        func::quitSDL(window, renderer);
        return 0;
    }

    /*bool load_sound = soundFunc::loadSound();
    if(load_sound == false){
        func::freeObj();
        func::quitSDL(window, renderer);
        return 0;
    }*/

    music = Mix_LoadMUS("sound/save_your_tears.wav");
    player_roc = Mix_LoadWAV("sound/player_rocket.wav");
    e_dis = Mix_LoadWAV("sound/enemy_disa.wav");
    col_e = Mix_LoadWAV("sound/col_e.wav");
    item_pick_up = Mix_LoadWAV("sound/item.wav");
    timelockSound = Mix_LoadWAV("sound/timelock.wav");
    butSound = Mix_LoadWAV("sound/evasion.wav");
    bmSound = Mix_LoadWAV("sound/bm.wav");
    Mix_VolumeChunk(col_e,30);
    Mix_VolumeChunk(item_pick_up,50);

    text_font = TTF_OpenFont("font/Montserrat-Regular.ttf",70);
    itemText_font = TTF_OpenFont("font/Montserrat-Regular.ttf",28);

    SDL_RenderClear(renderer);

    player car;                                                 //load player
    car.setRect(22 + 90 + (rand()%6)*90,550);
    car.loadImg("car/green.bmp",renderer);

    explosion expl;                                             //load explosion
    expl.loadImg("bgr/exp.bmp",renderer);
    expl.set_clip();

    enemy *ENEMYS = new enemy[enemy_quantity];                  //load enemy
    ENEMYS->loadEnemy(renderer,ENEMYS);

    item *p_item = new item[item_quantity];                     //load item
    p_item->loadItem(renderer,p_item);

    textObj ingameTextScore, ingameTextArm, ingameTextEv, ingameTextLock, ingameTextRoc;                                         //load text
    SDL_Color textColor, textColor0 = {255,255,255}, textColor100 = {51,153,255}, textColor200 = {255,51,255}, textColor500 = {255,102,102}, itemTextColor = {255,100,0};

    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    while(true){
        fps_timer.start();
        SDL_Delay(10);

        while(SDL_PollEvent(&event)){                                                                           //doi event
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
                func::freeObj();
                func::quitSDL(window,renderer);
                return 0;
            }
            car.inputKey(event,renderer,rocket_quantity,player_roc,music,musicPlayed);
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        imageFunc::load_bgr(renderer,speed_bgr,score,musicPlayed);                  //di chuyen man hinh

        car.show(renderer);
        car.loadPlayerAmmo(renderer);

        if(timelock) ENEMYS->lockSpeed(ENEMYS,speed_bgr);          //enemy mvment when + when not timelock
        else ENEMYS->changeSpeed(ENEMYS,score);
        //ENEMYS->ingameEnemy(ENEMYS,renderer,endGame,enemy_die,car.getRect(),car.getAmmo());

        Uint32 time = SDL_GetTicks()/1000;
        string time_val = to_string(time);
        //cout << time_val << endl;
        //cout << score << endl;
        for(int j = 0; j < enemy_quantity; j++){
            enemy *p_enemy = ENEMYS + j;
            SDL_Rect enemyRocket_rect;
            if(p_enemy != NULL){
                p_enemy->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT,score);                          //enemy move
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
                if(j == 7 || j == 5 || j == 4) p_enemy->enemyFire(SCREEN_WIDTH,SCREEN_HEIGHT,renderer,enemyRocket_rect,score);//dan
            }

            bool rocketed = imageFunc::collision(car.getRect(),enemyRocket_rect);               //dinh dan
            bool car_collision = imageFunc::collision(car.getRect(),p_enemy->getRect());        //dam xe
            if(car_collision){                          //fix rocket

                if(armor == 0){
                    Mix_PlayChannel(-1,col_e,0);
                    endGame = true;                    //va cham = endgame
                }
                Mix_PlayChannel(-1,e_dis,0);
                p_enemy->enemy_die();
                score += 1;
            }

            if(rocketed){
                if(evasion == 0){
                    Mix_PlayChannel(-1,col_e,0);
                    endGame = true;
                }
                //SDL_RenderPresent(renderer);
            }

            std::vector<rocket*> p_rocket = car.getAmmo();
            for(int i = 0; i < p_rocket.size(); i++){
                rocket *roc = p_rocket.at(i);
                if(roc != NULL){
                    bool rocket_collision = imageFunc::collision(roc->getRect(),p_enemy->getRect());        //ban trung
                    //bool roc_vs_roc = imageFunc::collision(roc->getRect(),enemyRocket_rect);                //2 rocket va cham
                    if(rocket_collision){
                        Mix_PlayChannel(-1,e_dis,0);
                        car.eraseRocket(i);
                        p_enemy->enemy_die();
                        score += 1;
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
                single_item->changeSpeed(p_item,speed_bgr);
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
                Mix_PlayChannel(-1,item_pick_up,0);
                single_item->picked(it,rocket_quantity,score,armor,evasion,timelock);
                if(it == 2){
                    Mix_PlayChannel(-1,timelockSound,0);
                }
                if(it == 3){
                    Mix_PlayChannel(-1,butSound,0);
                }

                if(it == 4){
                    Mix_PlayChannel(-1,bmSound,0);
                    car.changeCar(imageFunc::loadTexture("car/upgraded.bmp",renderer));                //fixing
                }
            }
        }

        imageFunc::renderTexture(imageFunc::loadTexture("item/cannon.bmp",renderer),renderer,5,300,itemW,itemH);
        string igRocQuan = to_string(rocket_quantity);
        if(!ingameTextRoc.loadFromRenderedText(igRocQuan,itemTextColor,itemText_font,renderer))              //fixing
        {
            cout << "Failed to render text texture!\n";
            func::freeObj();
            func::quitSDL(window,renderer);
            return 0;
        }
        if(rocket_quantity < 100) ingameTextRoc.renderText(55,305,clip,angle,center,flip,renderer);
        else ingameTextRoc.renderText(5,345,clip,angle,center,flip,renderer);

        if(armor > 0){                                      //armor time
            imageFunc::renderTexture(imageFunc::loadTexture("item/blademail.bmp",renderer),renderer,5,0,itemW,itemH);

            string timeArmor = to_string(4-armTime.size());
            if(!ingameTextArm.loadFromRenderedText(timeArmor,itemTextColor,itemText_font,renderer))              //fixing
            {
                cout << "Failed to render text texture!\n";
                func::freeObj();
                func::quitSDL(window,renderer);
                return 0;
            }
            ingameTextArm.renderText(55,5,clip,angle,center,flip,renderer);

            if(time_val != s1) armTime.push_back(time_val);
            s1 = time_val;
            //cout << time_val << endl;
            if(armTime.size() == armor*4){
                car.changeCar(imageFunc::loadTexture("car/green.bmp",renderer));
                rocket_quantity = 10;
                armor = 0;
                armTime.clear();
            }
        }

        if(timelock > 0){                                   //timelock time
            imageFunc::renderTexture(imageFunc::loadTexture("item/timelock.bmp",renderer),renderer,5,55,itemW,itemH);

            string timeLockSkill = to_string(4-lockTime.size());
            if(!ingameTextLock.loadFromRenderedText(timeLockSkill,itemTextColor,itemText_font,renderer))              //fixing
            {
                cout << "Failed to render text texture!\n";
                func::freeObj();
                func::quitSDL(window,renderer);
                return 0;
            }
            ingameTextLock.renderText(55,60,clip,angle,center,flip,renderer);

            if(time_val != s2) lockTime.push_back(time_val);                        //fixing
            s2 = time_val;
            if(lockTime.size() == timelock*4){
                timelock = 0;
                lockTime.clear();
            }
        }

        if(evasion > 0){                                    //evasion time
            imageFunc::renderTexture(imageFunc::loadTexture("item/butterfly.bmp",renderer),renderer,5,110,itemW,itemH);

            string timeEv = to_string(6-evTime.size());
            if(!ingameTextEv.loadFromRenderedText(timeEv,itemTextColor,itemText_font,renderer))              //fixing
            {
                cout << "Failed to render text texture!\n";
                func::freeObj();
                func::quitSDL(window,renderer);
                return 0;
            }
            ingameTextEv.renderText(55,115,clip,angle,center,flip,renderer);

            if(time_val != s3) evTime.push_back(time_val);                        //fixing
            s3 = time_val;
            if(evTime.size() == evasion*6){
                evasion = 0;
                evTime.clear();
            }
        }

        string igScore = to_string(score);
        if(0 <= score && score <= 99) textColor = textColor0;
        else if(100 <= score && score <= 199) textColor = textColor100;
        else if(200 <= score && score <= 499) textColor = textColor200;
        else textColor = textColor500;
        if(!ingameTextScore.loadFromRenderedText(igScore,textColor,text_font,renderer))              //fixing
        {
            printf( "Failed to render text texture!\n" );
            func::freeObj();
            func::quitSDL(window,renderer);
            return 0;
        }
        ingameTextScore.renderText(720,100,clip,angle,center,flip,renderer);                                      //fixing

        if(endGame == true){
            for(int exppp = 0; exppp < 4; exppp++){
                int x_pos = car.rect.x - exp_width*0.4;
                int y_pos = car.rect.y - exp_height*0.4;

                expl.set_frame(exppp);
                expl.setRect(x_pos,y_pos);
                if(exppp == 0) expl.renderTextureClip(renderer,x_pos,y_pos,&expl.clip[0]);
                else if(exppp == 1) expl.renderTextureClip(renderer,x_pos,y_pos,&expl.clip[1]);
                else if(exppp == 2) expl.renderTextureClip(renderer,x_pos,y_pos,&expl.clip[2]);
                else expl.renderTextureClip(renderer,x_pos,y_pos,&expl.clip[3]);

                SDL_Delay(30);
                SDL_RenderPresent(renderer);

            }
            SDL_Delay(1000);
            if(MessageBox(NULL,"YOU DIED","Message",MB_OK) == IDOK){
                delete []ENEMYS;
                delete []p_item;
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(control);
                func::quitSDL(window, renderer);
                return 0;
            }
        }

        SDL_RenderPresent(renderer);

        int real_time = fps_timer.get_tick();
        int time_one_frame = 1000/fps;
        if(real_time < time_one_frame){
            int delay_time = time_one_frame - real_time;
            if(delay_time >= 0) SDL_Delay(delay_time);
        }



    }

    delete []ENEMYS;
    delete []p_item;
    func::freeObj();
    func::quitSDL(window, renderer);
    return 0;
}


