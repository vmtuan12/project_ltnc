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
}

void func::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

    if (background == nullptr || control == nullptr) return false;

    return true;
}

void imageFunc::del_img_bgr()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(control);
}

void imageFunc::load_bgr(SDL_Renderer *ren, int &spBgr, int &scr)
{
    if(scr == 60) spBgr = 7;
    if(scr == 100) spBgr = 8;                                      //in progress
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
