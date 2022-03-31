#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <windows.h>
#include <string.h>
#include <SDL.h>
#include <vector>
#include <time.h>
#include <stdlib.h>


const int SCREEN_WIDTH = 1020;
const int SCREEN_HEIGHT = 650;
const int enemy_quantity = 8;
const int item_quantity = 5;
static int speed[4] = {8,9,10,11};

const std::string WINDOW_TITLE = "dep trai vkl";
static int bgr_y = 0;
static int speed_bgr = 6;

static SDL_Texture *background = NULL, *control = NULL;
static SDL_Event event;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
/*
static int rocket_quantity = 0;
static int HP = 20;
static int linken = 0;
static int blademail = 0;
*/
static int score = 0;


namespace func
{
    void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

    void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

    void waitUntilKeyPressed();
}

namespace imageFunc
{
    SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

    bool load_img_bgr(SDL_Renderer *ren);
    void del_img_bgr();

    void load_bgr(SDL_Renderer *ren);

    bool collision(const SDL_Rect &obj1, const SDL_Rect &obj2);
}




#endif // FUNCTION_H
