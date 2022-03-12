#include "inherited1.h"
#include "baseObject.h"
#include "function.h"

using namespace std;

int main(int argc, char* argv[])
{

    func::initSDL(window, renderer);

    SDL_Texture *background = imageFunc::loadTexture("bgr/road2.bmp", renderer);
    if (background == nullptr){
        SDL_DestroyTexture(background);
        func::quitSDL(window, renderer);
    }

    SDL_RenderClear(renderer);
    imageFunc::renderTexture(background, renderer, 0, 0, SCREEN_WIDTH-300, SCREEN_HEIGHT);
    SDL_Texture *car2 = imageFunc::loadTexture("car/black.bmp",renderer);
    inherited1 car;
    car.setRect(27,510);
    cout << car.rect.x << " " << car.rect.y << endl;
    car.obj = imageFunc::loadTexture("car/black.bmp",renderer);
    //car.show();
    imageFunc::renderTexture(car.obj,renderer,car.rect.x,car.rect.y,70,120);

    //SDL_Texture *car = imageFunc::loadTexture("car/black.bmp",renderer);
    //imageFunc::renderTexture(car,renderer,200,200);
    SDL_RenderPresent(renderer);

    while(true){
        SDL_Delay(10);

            // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&event) == 0) continue;

            // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (event.type == SDL_QUIT) break;
        if(event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_ESCAPE) break;
        car.inputKey(event);

        cout << car.rect.x << " " << car.rect.y << endl;

        SDL_RenderClear(renderer);
        imageFunc::renderTexture(background, renderer, 0, 0, SCREEN_WIDTH-300, SCREEN_HEIGHT);
        car.show();
        //imageFunc::renderTexture(car.obj,renderer,car.rect.x,car.rect.y,70,120);
        SDL_RenderPresent(renderer);
    }
    //func::waitUntilKeyPressed();

    //Giải phóng 2 biến texture đã dùng
    SDL_DestroyTexture(background);
    //Kết thúc SDL (giải phóng các biển window và renderer)
    func::quitSDL(window, renderer);
    return 0;
}
