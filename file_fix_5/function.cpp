#include "function.h"

void func::logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void func::initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        func::logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) func::logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) func::logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) func::logSDLError(std::cout, "CreateSound", true);

    if (TTF_Init() == -1) func::logSDLError(std::cout, "CreateFont", true);
}

void func::quitSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //if(window == NULL) std::cout << "1" << std::endl;
    //else std::cout << "0" << std::endl;
    renderer = NULL;
    window = NULL;

    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}

void func::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void func::getLetter(const SDL_Event &e, std::string &s, int &pos)
{
    if (e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_BACKSPACE)
            if(pos > 0) {pos -= 1; s[pos] = '_';}

        if('a' <= e.key.keysym.sym && e.key.keysym.sym <= 'z' ||
           '0' <= e.key.keysym.sym && e.key.keysym.sym <= '9')
        {
            if(s[9] == '_'){
                s[pos] = (char)e.key.keysym.sym;
                pos += 1;
            }
        }
        if(e.key.keysym.sym == SDLK_SPACE){
            s[pos] = ' ';
            pos += 1;
        }
    }
}

void func::textColorChange(int &r, int &g, int &b)
{
    if(r < 255) r++;
    else r = 0;
    if(g < 254) g += 2;
    else g = 0;
    if(b < 253) b += 3;
    else b = 0;
}

void func::resetInt(int &scr, int &bgrY, int &sp_bgr, int &roc_quan, int &posY_name)
{
    scr = 0;
    bgrY = 0;
    sp_bgr = 6;
    roc_quan = 10;
    posY_name = -650;
}

SDL_Texture* imageFunc::loadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			func::logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		func::logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

void imageFunc::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void imageFunc::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

bool imageFunc::load_img_bgr(SDL_Renderer *ren)
{
    background = imageFunc::loadTexture("bgr/road4-overlay-overlay.bmp", ren);
    control = imageFunc::loadTexture("bgr/control.bmp",ren);
    crash = imageFunc::loadTexture("bgr/die.bmp",ren);
    upgraded = imageFunc::loadTexture("car/upgraded.bmp",ren);
    basicCar = imageFunc::loadTexture("car/green.bmp",ren);
    iLock = imageFunc::loadTexture("item/timelock.bmp",ren);
    iEv = imageFunc::loadTexture("item/butterfly.bmp",ren);
    iBm = imageFunc::loadTexture("item/blademail.bmp",ren);

    if (background == nullptr || control == nullptr || upgraded == nullptr || basicCar == nullptr ||
        iLock == nullptr || iEv == nullptr || iBm == nullptr || crash == nullptr)
            return false;

    return true;
}

bool imageFunc::load_img_menuPhase(SDL_Renderer *ren)
{
    menu = imageFunc::loadTexture("bgr/fixing.bmp",ren);
    naming = imageFunc::loadTexture("bgr/naming.bmp",ren);
    congrat = imageFunc::loadTexture("bgr/congrat.bmp",ren);

    if (menu == nullptr || naming == nullptr || congrat == nullptr) return false;
    return true;
}

void imageFunc::iLockRen(SDL_Renderer *ren)
{
    imageFunc::renderTexture(iLock,ren,100,10,30,30);
}

void imageFunc::iEvRen(SDL_Renderer *ren)
{
    imageFunc::renderTexture(iEv,ren,135,10,30,30);
}

void imageFunc::iBmRen(SDL_Renderer *ren)
{
    imageFunc::renderTexture(iBm,ren,170,10,30,30);
}

void imageFunc::menuRen(SDL_Renderer *ren)
{
    imageFunc::renderTexture(menu,ren,0,0);
}

void imageFunc::namingRen(SDL_Renderer *ren, int &y)
{
    if(y != 0) y += 10;
    imageFunc::renderTexture(naming,ren,0,y,SCREEN_WIDTH,SCREEN_HEIGHT*2);
}

void imageFunc::congratRen(SDL_Renderer *ren, int &y, SDL_Event e, bool &conf, Mix_Chunk *but)
{
    while(SDL_PollEvent(&e)){                                                                           //doi event
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) conf = true;
        Mix_PlayChannel(-1,but,0);
    }
    SDL_RenderClear(ren);
    if(y != 0) y += 10;
    imageFunc::renderTexture(congrat,ren,0,y,SCREEN_WIDTH,SCREEN_HEIGHT*2);
}

void imageFunc::crashRen(SDL_Renderer *ren)
{
    imageFunc::renderTexture(crash,ren,0,0);
    SDL_RenderPresent(ren);
    SDL_Delay(2000);
}

void imageFunc::del_img_bgr()
{

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(control);
    SDL_DestroyTexture(crash);
    SDL_DestroyTexture(upgraded);
    SDL_DestroyTexture(basicCar);
    SDL_DestroyTexture(iLock);
    SDL_DestroyTexture(iEv);
    SDL_DestroyTexture(iBm);

    background = NULL;
    control = NULL;
    crash = NULL;
    upgraded = NULL;
    basicCar = NULL;
    iLock = NULL;
    iEv = NULL;
    iBm = NULL;

    //if(control == NULL) std::cout << "1" << std::endl;
    //else std::cout << "0" << std::endl;

}

void imageFunc::del_img_menuPhase()
{
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(naming);
    SDL_DestroyTexture(congrat);
    menu = NULL;
    congrat = NULL;
    naming = NULL;
}

void imageFunc::load_bgr(SDL_Renderer *ren, int &spBgr, int &scr)
{
    if(scr == 60) spBgr = 7;
    if(scr == 100) spBgr = 8;                                      //in progress
    if(scr == 200) spBgr = 9;
    bgr_y += spBgr;           //toc do di chuyen man hinh

    imageFunc::renderTexture(background, ren, 0, bgr_y, 720, SCREEN_HEIGHT);
    imageFunc::renderTexture(background, ren, 0, bgr_y-SCREEN_HEIGHT, 720, SCREEN_HEIGHT);
    imageFunc::renderTexture(control, ren, 720, 0);
    if(bgr_y >= SCREEN_HEIGHT) bgr_y = 0;
}

bool imageFunc::collision(const SDL_Rect &obj1, const SDL_Rect &obj2)                 //need to fix
{
    int left_obj1 = obj1.x;
    int right_obj1 = obj1.x + obj1.w;
    int top_obj1 = obj1.y;
    int bot_obj1 = obj1.y + obj1.h;

    int left_obj2 = obj2.x;
    int right_obj2 = obj2.x + obj2.w;
    int top_obj2 = obj2.y;
    int bot_obj2 = obj2.y + obj2.h;

    //std::cout << top_obj1 << std::endl;
    //if(top_obj1 < 500) return true;

    if (left_obj1 >= left_obj2 && left_obj1 <= right_obj2){
        if (top_obj1 >= top_obj2 && top_obj1 <= bot_obj2) return true;
    }

    if (left_obj1 >= left_obj2 && left_obj1 <= right_obj2){
        if (bot_obj1 >= top_obj2 && bot_obj1 <= bot_obj2) return true;
    }

    if (right_obj1 >= left_obj2 && right_obj1 <= right_obj2){
        if (top_obj1 >= top_obj2 && top_obj1 <= bot_obj2) return true;
    }

    if (right_obj1 >= left_obj2 && right_obj1 <= right_obj2){
        if (bot_obj1 >= top_obj2 && bot_obj1 <= bot_obj2) return true;
    }

    if (left_obj2 >= left_obj1 && left_obj2 <= right_obj1){
        if (top_obj2 >= top_obj1 && top_obj2 <= bot_obj1) return true;

    }

    if (left_obj2 >= left_obj1 && left_obj2 <= right_obj1){
        if (bot_obj2 >= top_obj1 && bot_obj2 <= bot_obj1) return true;
    }

    if (right_obj2 >= left_obj1 && right_obj2 <= right_obj1){
        if (top_obj2 >= top_obj1 && top_obj2 <= bot_obj1) return true;
    }

    if (right_obj2 >= left_obj1 && right_obj2 <= right_obj1){
        if (bot_obj2 >= top_obj1 && bot_obj2 <= bot_obj1) return true;
    }

    if (top_obj1 == top_obj2 && right_obj1 == right_obj2 && bot_obj1 == bot_obj2) return true;

    return false;
}
