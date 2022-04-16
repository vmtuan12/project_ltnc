#include "side_obj.h"

item::item()
{
    x_val = 0;
    y_val = 0;

    rect.x = 0;
    rect.y = 0;
    rect.w = itemW;
    rect.h = itemH;
}

item::~item()
{

}

void item::movingControl(int const &x_limit, int const &y_limit)
{
    srand((int)time(0));
    rect.y += y_val;

    if(rect.y >= y_limit){
        int rand_x = 1 + rand()%6;
        rect.x = 22 + 90 + (rand_x-1)*90;

        rect.y = -1000;
    }
}

void item::loadItem(SDL_Renderer *ren, item *p_item)
{
    srand((int)time(0));
    int rand_x, rand_y;

    for(int i = 0; i < item_quantity; i++){
        item *single_item = p_item + i;

        if(single_item != NULL){
            if(i == 0) single_item->loadImg("item/1p.bmp",ren);
            else if(i == 1) single_item->loadImg("item/cannon.bmp",ren);
            else if(i == 2) single_item->loadImg("item/timelock.bmp",ren);
            else if(i == 3) single_item->loadImg("item/butterfly.bmp",ren);
            else single_item->loadImg("item/blademail.bmp",ren);

            rand_x = 1 + rand()%6;
            rand_y = 100 + rand()%(120 + 1 - 100);
            single_item->setRect(22 + 90 + (rand_x-1)*90,-i*rand_y);
            single_item->set_y(speed_bgr);                                       //set y_val cho speed
        }
    }

}

void item::ingameItem(item *p_item, SDL_Renderer *ren)
{
    for(int i = 0; i < item_quantity; i++){
        item *single_item = p_item + i;

        if(single_item != NULL){
            single_item->itemShow(ren);
            single_item->movingControl(SCREEN_WIDTH,SCREEN_HEIGHT);
        }
    }

}

void item::picked(const int &pos, int &roc_quan, int &p, int &arm, int &evade, int &tLock)
{
    srand((int)time(0));
    if(pos == 0){
        rect.y -= 1000;
        p++;
    }
    else if(pos == 1){                              //add butterfly + timelock
        rect.y -= 1000;
        roc_quan++;
    }
    else if(pos == 2){
        rect.y -= 6000;
        tLock += 1;
    }
    else if(pos == 3){
        rect.y -= 5000;
        evade += 1;
    }
    else{
        rect.y -= 5000;
        arm += 1;
        roc_quan = 1000;
    }
    rect.x = 22 + 90 + (1 + rand()%6 - 1)*90;
}

void item::changeSpeed(item *p_item, int &spBgr)
{
    /*if(scr >= 60){
        for(int j = 0; j < enemy_quantity; j++){
            item *single_item = p_item + j;
            single_item->set_y(7);
        }
    }
    if(scr >= 100){
        for(int j = 0; j < enemy_quantity; j++){
            item *single_item = p_item + j;
            single_item->set_y(8);
        }
    }*/
    for(int j = 0; j < enemy_quantity; j++){
        item *single_item = p_item + j;
        single_item->set_y(spBgr);
    }
}
