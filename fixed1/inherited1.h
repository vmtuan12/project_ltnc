#ifndef INHERITED1_H
#define INHERITED1_H

#include "baseObject.h"

const int OBJ_WIDTH = 70;
const int OBJ_HEIGHT = 120;

class inherited1 : public baseObject
{
public:
    inherited1();
    ~inherited1();

    void inputKey(SDL_Event e);
    int x_val;
    int y_val;
};

#endif // INHERITED1_H
