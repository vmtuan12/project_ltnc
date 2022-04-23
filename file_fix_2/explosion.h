#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "baseObject.h"
#include "function.h"

const int exp_width = 250;  //250
const int exp_height = 208; //208

class explosion : public baseObject
{
public:
    explosion();
    ~explosion();
    void set_clip();
    void set_frame(const int &frame_) {frame = frame_;}

    SDL_Rect clip[4];

    void renderTextureClip(SDL_Renderer *ren,const int &x,const int &y, SDL_Rect *clip_);
private:
    int frame;


};

#endif // EXPLOSION_H
