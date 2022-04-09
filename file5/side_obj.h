#ifndef SIDE_OBJ_H
#define SIDE_OBJ_H

#include "baseObject.h"
#include "function.h"
#include "player.h"

class item : public baseObject
{
public:
    item();
    ~item();

    void setSize(const int &w, const int &h){
        rect.w = w;
        rect.h = h;
    }
    void set_x(const int val) {x_val = val;}
    void set_y(const int val) {y_val = val;}
    int get_x() const {return x_val;}
    int get_y() const {return y_val;}

    void loadItem(SDL_Renderer *ren, item *p_item);
    void movingControl(int const &x_limit, int const &y_limit);

    void ingameItem(item *p_item, SDL_Renderer *ren);
    void picked(const int &pos, int &roc_quan, int &p);

private:
    int x_val;
    int y_val;

};

#endif // SIDE_OBJ_H
