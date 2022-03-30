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
            else if(i == 2) single_item->loadImg("item/regen.bmp",ren);
            else if(i == 3) single_item->loadImg("item/linken.bmp",ren);
            else single_item->loadImg("item/blademail.bmp",ren);

            rand_x = 1 + rand()%6;
            rand_y = 100 + rand()%(120 + 1 - 100);
            single_item->setRect(22 + 90 + (rand_x-1)*90,-i*rand_y);
            single_item->set_y(3);                                       //set y_val cho speed
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
