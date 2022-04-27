#include "player.h"
#include "baseObject.h"
#include "function.h"
#include "rocket.h"
#include "enemy.h"
#include "side_obj.h"
#include "timer.h"
#include "text.h"
#include "explosion.h"

using namespace std;

int main(int argc, char* argv[])
{

    timer fps_timer;
    srand((int)time(0));

    ifstream infile;
    ofstream outfile;
    infile.open("high_score.txt");          //read from text
    string lordName;
    getline(infile,lordName,':');
    int lordScore;
    infile >> lordScore;
    infile.close();

    func::initSDL(window, renderer);

    bool load_img = imageFunc::load_img_bgr(renderer);
    if(load_img == false){
        cout << "false load img and bgr" << endl;
        imageFunc::del_img_bgr();
        func::quitSDL();
    }

    bool load_sound_and_text = func::loadSoundText();
    if(load_sound_and_text == false){
        cout << "false sound and text";
        imageFunc::del_img_bgr();
        func::quitSDL();
        return 0;
    }

    textObj playText, exitText, scoreText, nameText, highScoreName, highScoreInt;
    SDL_Color scoreU100 = {255,255,255}, scoreU200 = {51,153,255}, scoreU500 = {255,51,255}, scoreO500 = {255,102,102};
    SDL_Color textColorPlay = {0,128,255}, textColorExit = {0,128,255};
    SDL_Color colorScore;

    while(true)
    {
        SDL_Delay(10);
        while(SDL_PollEvent(&menuEvent)){
            if (menuEvent.type == SDL_QUIT || (menuEvent.type == SDL_KEYDOWN && menuEvent.key.keysym.sym == SDLK_ESCAPE)){
                imageFunc::del_img_bgr();
                func::del_sound_text();
                func::quitSDL();
                return 0;
            }
            if(menuEvent.type == SDL_MOUSEMOTION){
                if(75 <= menuEvent.motion.x && menuEvent.motion.x <= 230 && 250 <= menuEvent.motion.y && menuEvent.motion.y <= 340){
                    textColorPlay = {255,102,102};

                }
                else textColorPlay = {0,128,255};

                if(75 <= menuEvent.motion.x && menuEvent.motion.x <= 230 && 365 <= menuEvent.motion.y && menuEvent.motion.y <= 455){
                    textColorExit = {255,102,102};
                }
                else textColorExit = {0,128,255};
            }
            if(menuEvent.type == SDL_MOUSEBUTTONDOWN){
                if(75 <= menuEvent.button.x && menuEvent.button.x <= 230 && 250 <= menuEvent.button.y && menuEvent.button.y <= 340){
                    playGame = true;
                    textColorPlay = {0,128,255};
                }
                if(75 <= menuEvent.button.x && menuEvent.button.x <= 230 && 365 <= menuEvent.button.y && menuEvent.button.y <= 455){
                    imageFunc::del_img_bgr();
                    func::del_sound_text();
                    //if(gFont == NULL) std::cout << "1" << std::endl;
                    //else std::cout << "0" << std::endl;
                    func::quitSDL();
                    return 0;
                }
            }
        }

        if(playGame){
            //code here

            infile.open("high_score.txt");          //read from text
            string playerName;
            getline(infile,playerName,':');
            int highScore;
            infile >> highScore;
            //cout << s << endl << a;

            string name = "__________";
            bool enterName = false;
            int pos = 0;
            while(playGame){
                while(SDL_PollEvent(&nameEvent)){                                                                           //doi event
                    if (nameEvent.type == SDL_QUIT || (nameEvent.type == SDL_KEYDOWN && nameEvent.key.keysym.sym == SDLK_ESCAPE)){
                        playGame = false;
                        break;
                    }
                    if (nameEvent.type == SDL_KEYDOWN && nameEvent.key.keysym.sym == SDLK_RETURN){
                        enterName = true;
                        break;
                    }
                    func::getLetter(nameEvent,name,pos);
                }

                if(enterName){
                    break;
                    enterName = false;
                }
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                imageFunc::namingRen(renderer,pos_y_naming);
                if(!nameText.loadFromRenderedText(name,{52,52,255},nameFont,renderer))              //fixing
                {
                    cout << "Failed to render text name texture!\n";
                    imageFunc::del_img_bgr();
                    func::del_sound_text();
                    func::quitSDL();
                    return 0;
                }
                int name_x = SCREEN_WIDTH/2 - nameText.getWidth()/2;
                if(pos_y_naming == 0) nameText.renderText(name_x,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                SDL_RenderPresent(renderer);
            }

            while(true){
                if(name[name.length()-1] == ' ' || name[name.length()-1] == '_') name.erase(name.begin()+name.length()-1);
                else break;
            }

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

            bool isOut = false;
            while(playGame){
                fps_timer.start();
                //SDL_Delay(10);

                while(SDL_PollEvent(&event)){                                                                           //doi event
                    if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
                        delete []ENEMYS;
                        delete []p_item;
                        ENEMYS = NULL;
                        p_item = NULL;
                        isOut = true;
                        playGame = false;
                    }
                    car.inputKey(event,renderer,rocket_quantity,fire);
                }
                if(isOut) break;
                SDL_RenderClear(renderer);                      //load bgr + car

                imageFunc::load_bgr(renderer,speed_bgr,score);                  //di chuyen man hinh

                car.show(renderer);
                car.loadPlayerAmmo(renderer);                   //load rocket cho player

                if(timelock) ENEMYS->lockSpeed(ENEMYS,speed_bgr);
                else ENEMYS->changeSpeed(ENEMYS,score);


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
                                break;
                            }
                        }
                        //
                        p_enemy->show(renderer);
                        if(j == 7 || j == 5 || j == 4) p_enemy->enemyFire(SCREEN_WIDTH,SCREEN_HEIGHT,renderer,enemyRocket_rect,score);//dan
                    }

                    bool rocketed = imageFunc::collision(car.getRect(),enemyRocket_rect);               //dinh dan
                    bool car_collision = imageFunc::collision(car.getRect(),p_enemy->getRect());        //dam xe
                    //cout << p_enemy->getRect().x << " " << p_enemy->getRect().y << endl;
                     if(car_collision){                          //fix rocket

                        if(armor == 0){
                            Mix_PlayChannel(-1,explode,0);
                            endGame = true;                    //va cham = endgame
                            //SDL_RenderPresent(renderer);
                        }
                        Mix_PlayChannel(-1,e_dis,0);
                        p_enemy->enemy_die();
                    }

                    if(rocketed){
                        if(evasion == 0){
                            Mix_PlayChannel(-1,explode,0);
                            endGame = true;
                        }
                        //SDL_RenderPresent(renderer);
                    }

                    std::vector<rocket*> p_rocket = car.getAmmo();
                    for(int i = 0; i < p_rocket.size(); i++){
                        rocket *roc = p_rocket.at(i);
                        if(roc != NULL){
                            bool rocket_collision = imageFunc::collision(roc->getRect(),p_enemy->getRect());        //ban trung
                            if(rocket_collision){
                                Mix_PlayChannel(-1,e_dis,0);
                                car.eraseRocket(i);
                                p_enemy->enemy_die();
                            }
                        }
                    }

                }

                string screenScore = to_string(score);
                if(score < 100) colorScore = scoreU100;
                else if(score < 200) colorScore = scoreU200;
                else if(score < 500) colorScore = scoreU500;
                else colorScore = scoreO500;
                if(!scoreText.loadFromRenderedText(screenScore,colorScore,gFont,renderer))              //fixing
                {
                    cout << "Failed to render text texture!\n" << endl;
                    imageFunc::del_img_bgr();
                    func::del_sound_text();
                    //if(gFont == NULL) std::cout << "1" << std::endl;
                    //else std::cout << "0" << std::endl;
                    func::quitSDL();
                    return 0;
                }
                scoreText.renderText(720,120,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

                for(int it = 0; it < item_quantity; it++){
                    item *single_item = p_item + it;

                    if(single_item != NULL){
                        single_item->itemShow(renderer);
                        single_item->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);
                        single_item->changeSpeed(p_item,score);
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
                        Mix_PlayChannel(-1,item_picked,0);
                        single_item->picked(it,rocket_quantity,score,armor,evasion,timelock);
                        if(it == 4){
                            car.changeCar(imageFunc::loadTexture("car/upgraded.bmp",renderer));                //fixing
                        }
                    }
                }

                if(armor > 0){                                      //armor time
                    imageFunc::iBmRen(renderer);
                    if(time_val != s1) armTime.push_back(time_val);
                    s1 = time_val;
                    //cout << time_val << endl;
                    if(armTime.size() == armor*4){
                        s1 = "-1";
                        car.changeCar(imageFunc::loadTexture("car/green.bmp",renderer));
                        rocket_quantity = 10;
                        armor = 0;
                        armTime.clear();
                    }
                }

                if(timelock > 0){                                   //timelock time
                    imageFunc::iLockRen(renderer);
                    if(time_val != s2) lockTime.push_back(time_val);                        //fixing
                    s2 = time_val;
                    if(lockTime.size() == timelock*4){
                        s2 = "-1";
                        timelock = 0;
                        lockTime.clear();
                    }
                }

                if(evasion > 0){                                    //evasion time
                    imageFunc::iEvRen(renderer);
                    if(time_val != s3) evTime.push_back(time_val);                        //fixing
                    s3 = time_val;
                    if(evTime.size() == evasion*6){
                        s3 = "-1";
                        evasion = 0;
                        evTime.clear();
                    }
                }

                if(endGame == true){
                    endGame = false;
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
                    if(MessageBox(NULL,"YOU DIED","Message",MB_OK) == IDOK){
                        delete []ENEMYS;
                        delete []p_item;
                        ENEMYS = NULL;
                        p_item = NULL;
                        playGame = false;
                        break;
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

            outfile.open("high_score.txt");
            if(score >= highScore){
                lordName = name;
                lordScore = score;
                outfile << name << ": " << score;
            }
            else{
                outfile << lordName << ": " << lordScore;
            }
            infile.close();
            outfile.close();

            armor = 0, timelock = 0, evasion = 0;
            func::resetInt(score,bgr_y,speed_bgr,rocket_quantity,pos_y_naming);
            delete []ENEMYS;
            delete []p_item;
            ENEMYS = NULL;
            p_item = NULL;
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        imageFunc::menuRen(renderer);

        func::textColorChange(red,green,blue);
        if(!highScoreName.loadFromRenderedText(lordName,{red-30,green+50,blue+70},nameFont,renderer))              //fixing
        {
            cout << "Failed to render text texture!\n";
            imageFunc::del_img_bgr();
            func::del_sound_text();
            //if(gFont == NULL) std::cout << "1" << std::endl;
            //else std::cout << "0" << std::endl;
            func::quitSDL();
            return 0;
        }
        if(!highScoreInt.loadFromRenderedText(to_string(lordScore),{red,green,blue},nameFont,renderer))              //fixing
        {
            cout << "Failed to render text texture!\n";
            imageFunc::del_img_bgr();
            func::del_sound_text();
            //if(gFont == NULL) std::cout << "1" << std::endl;
            //else std::cout << "0" << std::endl;
            func::quitSDL();
            return 0;
        }
        if(!exitText.loadFromRenderedText("EXIT",textColorExit,gFont,renderer))              //fixing
        {
            cout << "Failed to render text texture!\n";
            imageFunc::del_img_bgr();
            func::del_sound_text();
            //if(gFont == NULL) std::cout << "1" << std::endl;
            //else std::cout << "0" << std::endl;
            func::quitSDL();
            return 0;
        }
        if(!playText.loadFromRenderedText("PLAY",textColorPlay,gFont,renderer))              //fixing
        {
            cout << "Failed to render text texture!\n";
            imageFunc::del_img_bgr();
            func::del_sound_text();
            //if(gFont == NULL) std::cout << "1" << std::endl;
            //else std::cout << "0" << std::endl;
            func::quitSDL();
            return 0;
        }
        playText.renderText(87,262,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        exitText.renderText(95,377,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        highScoreName.renderText(685-highScoreName.getWidth()/2,120,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        highScoreInt.renderText(685-highScoreInt.getWidth()/2,200,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

        SDL_RenderPresent(renderer);

    }

    imageFunc::del_img_bgr();
    func::del_sound_text();
    func::quitSDL();
    return 0;
}

bool func::loadSoundText()
{
    gFont = TTF_OpenFont("font/Montserrat-Regular.ttf",50);
    nameFont = TTF_OpenFont("font/Montserrat-Regular.ttf",70);

    item_picked = Mix_LoadWAV("sound/item.wav");
    fire = Mix_LoadWAV("sound/player_rocket.wav");
    explode = Mix_LoadWAV("sound/col_e.wav");
    e_dis = Mix_LoadWAV("sound/enemy_disa.wav");
    if(gFont == NULL || item_picked == NULL || fire == NULL || explode == NULL || e_dis == NULL){
        return false;
    }
    return true;
}

void func::del_sound_text()
{
    //if(fire == NULL) std::cout << "1" << std::endl;
    //else std::cout << "0" << std::endl;
    TTF_CloseFont(gFont);
    TTF_CloseFont(nameFont);
    Mix_FreeChunk(item_picked);
    Mix_FreeChunk(fire);
    Mix_FreeChunk(explode);
    Mix_FreeChunk(e_dis);

    gFont = NULL;
    nameFont = NULL;
    item_picked = NULL;
    fire = NULL;
    explode = NULL;
    e_dis = NULL;
    //if(fire == NULL) std::cout << "1" << std::endl;
    //else std::cout << "0" << std::endl;
}
