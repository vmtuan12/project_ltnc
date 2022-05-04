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
#include <fstream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int SCREEN_WIDTH = 1020;
const int SCREEN_HEIGHT = 650;
const int enemy_quantity = 8;
const int item_quantity = 5;
static int speed[4] = {8,9,10,12};  //8
static int rocSpeed[3] = {12,14,16};//12

const std::string WINDOW_TITLE = "dep trai vkl";
static int bgr_y = 0;
static int speed_bgr = 6;
static int pos_y_naming = -650;

static SDL_Texture *background = NULL, *control = NULL, *menu = NULL, *naming = NULL, *congrat = NULL, *crash = NULL;
static SDL_Texture *upgraded = NULL, *basicCar = NULL, *iLock = NULL, *iEv = NULL, *iBm = NULL;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Event event, menuEvent, nameEvent;

const int fps = 60;

static int rocket_quantity = 10;
static int armor = 0, evasion = 0, timelock = 0;
static int score = 0;

static bool playGame = false, endGame = false;
static std::string s1 = "-1", s2 = "-1", s3 = "-1";
static std::vector<std::string> armTime, evTime, lockTime;

static Mix_Chunk *item_picked = NULL, *fire = NULL, *explode = NULL, *e_dis = NULL,
                 *button = NULL, *letsgo = NULL, *wow = NULL;
static TTF_Font *gFont = NULL, *nameFont = NULL;
static int red = 150, green = 250, blue = 50;

namespace func
{
    void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

    void quitSDL();

    void waitUntilKeyPressed();

    bool loadSoundText();
    void del_sound_text();

    void getLetter(const SDL_Event &e, std::string &s, int &pos);
    void textColorChange(int &r, int &g, int &b);

    void resetInt(int &scr, int &bgrY, int &sp_bgr, int &roc_quan, int &posY_name);

}

namespace imageFunc
{
    SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

    bool load_img_bgr(SDL_Renderer *ren);
    bool load_img_menuPhase(SDL_Renderer *ren);
    void del_img_bgr();
    void del_img_menuPhase();

    void iLockRen(SDL_Renderer *ren);
    void iEvRen(SDL_Renderer *ren);
    void iBmRen(SDL_Renderer *ren);
    void menuRen(SDL_Renderer *ren);
    void namingRen(SDL_Renderer *ren, int &y);
    void congratRen(SDL_Renderer *ren, int &y, SDL_Event e, bool &conf, Mix_Chunk *but);
    void crashRen(SDL_Renderer *ren);

    void load_bgr(SDL_Renderer *ren, int &spBgr, int &scr);

    bool collision(const SDL_Rect &obj1, const SDL_Rect &obj2);


}




#endif // FUNCTION_H
