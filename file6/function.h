#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <windows.h>
#include <string.h>
#include <SDL.h>
#include <vector>
#include <time.h>
#include <sstream>
#include <stdlib.h>

const int SCREEN_WIDTH = 1020;
const int SCREEN_HEIGHT = 650;
const int enemy_quantity = 8;
const int item_quantity = 5;
static int speed[4] = {8,9,10,11};  //8
static int rocSpeed[3] = {12,13,14};//12

const std::string WINDOW_TITLE = "dep trai vkl";
static int bgr_y = 0;
static int speed_bgr = 6;

static SDL_Texture *background = NULL, *control = NULL;
static SDL_Event event;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int fps = 200;

static int rocket_quantity = 10;
static bool evasion = false;
static bool timelock = false;
static int score = 0;
static int armor = 0;

static bool endGame = false;
static std::string s1 = "-1", s2 = "-1", s3 = "-1";
static std::vector<std::string> armTime, evTime, lockTime;


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

    void load_bgr(SDL_Renderer *ren, int &spBgr, int &scr);

    bool collision(const SDL_Rect &obj1, const SDL_Rect &obj2);
}




#endif // FUNCTION_H
