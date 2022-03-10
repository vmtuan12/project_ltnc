#include <iostream>
#include <SDL.h>
#include "header.h"
//#include <SDL2/SDL.h>

using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 650;
const string WINDOW_TITLE = "gem dua xe cua tuan dz";

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[])
{

    initSDL(window, renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    load_image(window,renderer);                            // add ảnh

    //Xoá màn hình
    SDL_RenderClear(renderer);
    int x = 27.5, y = 510, w = 70, h = 120; // tọa độ đầu tiên và size của xe
    SDL_Event e;

    // Bước nhảy mỗi khi dịch chuyển
    int step = 125;
    // Xoá toàn bộ màn hình và vẽ
    refreshScreen(window, car, renderer,x,y,w,h,SCREEN_HEIGHT,SCREEN_WIDTH);

    while (true) {
        // Đợi 10 mili giây
        SDL_Delay(10);

        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&e) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;

        // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
        if (e.type == SDL_KEYDOWN) {
            // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
            if (e.key.keysym.sym == SDLK_ESCAPE) break;
            // (cộng chiều rộng, trừ bước, rồi lấy phần dư để giá trị luôn dương, và hiệu ứng quay vòng)
            if (e.key.keysym.sym == SDLK_a){
                step = 125;
                if(x > 125) x = (x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
            }
            if (e.key.keysym.sym == SDLK_d){
                step = 125;
                if(x < 375) x = (x + step) % SCREEN_WIDTH;
            }
            if (e.key.keysym.sym == SDLK_s){
                step = 60;
                if(y != 510) y = (y + step) % SCREEN_HEIGHT;
            }
            if (e.key.keysym.sym == SDLK_w){
                step = 60;
                if(y > 100) y = (y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
            }

            // Xoá toàn bộ màn hình và vẽ lại
            refreshScreen(window,car, renderer,x,y,w,h,SCREEN_HEIGHT,SCREEN_WIDTH);
        }
    }

    quitSDL(window, renderer);
    del_image();
    return 0;
}

void del_image()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(car);
    SDL_DestroyTexture(linken);
    SDL_DestroyTexture(regen);
    SDL_DestroyTexture(control);
}
//**************************************************************

