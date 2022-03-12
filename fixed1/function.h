#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <windows.h>
#include <string.h>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 650;
const std::string WINDOW_TITLE = "An Implementation of Code.org Painter";

//static SDL_Texture *background = NULL, *control = NULL, *car = NULL;
static SDL_Event event;
static SDL_Window* window;
static SDL_Renderer* renderer;

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

    //void moving(SDL_Event e, int &x, int &y, int &step);
}




#endif // FUNCTION_H
