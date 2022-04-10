#include "explosion.h"

explosion::explosion()
{

}

explosion::~explosion()
{

}

void explosion::set_clip()
{

    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = exp_width;
    clip[0].h = exp_height;

    clip[1].x = exp_width;
    clip[1].y = 0;
    clip[1].w = exp_width;
    clip[1].h = exp_height;

    clip[2].x = exp_width*2;
    clip[2].y = 0;
    clip[2].w = exp_width;
    clip[2].h = exp_height;

    clip[3].x = exp_width*3;
    clip[3].y = 0;
    clip[3].w = exp_width;
    clip[3].h = exp_height;
}

void explosion::renderTextureClip(SDL_Renderer *ren, int x, int y, SDL_Rect *clip_)
{

    SDL_Rect dst;
    dst.x = x;
	dst.y = y;
	dst.w = clip_->w;
	dst.h = clip_->h;
	SDL_RenderCopy(ren, this->obj, clip_, &dst);
}
