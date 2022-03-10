#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <SDL.h>
#include <string.h>

static SDL_Texture *background, *control, *car, *linken, *regen;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             int SCREEN_WIDTH, int SCREEN_HEIGHT, const std::string WINDOW_TITLE);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
//**************************************************************

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void load_image(SDL_Window *window, SDL_Renderer* renderer);
void del_image();
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void refreshScreen(SDL_Window* window, SDL_Texture *tex, SDL_Renderer* renderer,
                   int x, int y, int w, int h, int SCREEN_HEIGHT, int SCREEN_WIDTH);

#endif
