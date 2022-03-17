#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <windows.h>
#include <string.h>
#include <SDL.h>
#include <vector>
#include <time.h>
#include <stdlib.h>


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 650;
const int enemy_x_position[6] = {40,190,340,490,640,790};
const std::string WINDOW_TITLE = "dep trai vkl";

static SDL_Texture *background = NULL, *control = NULL;
static SDL_Event event;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
/*
static int rocket_quantity = 0;
static int HP = 20;
static int linken = 0;
static int blademail = 0;
static int point = 0;
*/

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
}




#endif // FUNCTION_H
