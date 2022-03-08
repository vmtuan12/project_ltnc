#include <iostream>
#include <SDL.h>
//#include <SDL2/SDL.h>

using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "gem dua xe cua tuan dz";

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
//**************************************************************

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void refreshScreen(SDL_Window* window, SDL_Texture *tex, SDL_Renderer* renderer, int x, int y, int w, int h);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture *background = loadTexture("road2.bmp", renderer);
    SDL_Texture *image = loadTexture("black.bmp", renderer);
    SDL_Texture *linken = loadTexture("linken.bmp",renderer);
    SDL_Texture *regen = loadTexture("regen.bmp",renderer);
    if (background == nullptr || image == nullptr){
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(image);
        quitSDL(window, renderer);
    }

    //Xoá màn hình
    SDL_RenderClear(renderer);

    //Vẽ ảnh nền vào toàn bộ cửa sổ
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    int x = 35, y = 630, w = 80, h = 160;
    renderTexture(image, renderer, 35, 630, 80, 160);
    renderTexture(linken, renderer, 35, 10, 80, 80);
    renderTexture(regen, renderer, 35, 10, 80, 80);
    // Your code here
    SDL_Event e;

    // Định nghĩa toạ độ ban đầu và kích cỡ hình chữ nhật
    /*
    SDL_Rect filled_rect;
    filled_rect.x = 35;
    filled_rect.y = 630;
    filled_rect.w = 80;
    filled_rect.h = 160;
    */
    // Bước nhảy mỗi khi dịch chuyển
    int step = 150;
    // Xoá toàn bộ màn hình và vẽ
    refreshScreen(window, image, renderer,x,y,w,h);

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

            // Nếu phím mũi tên trái, dịch sang trái
            // (cộng chiều rộng, trừ bước, rồi lấy phần dư để giá trị luôn dương, và hiệu ứng quay vòng)
            if (e.key.keysym.sym == SDLK_LEFT){
                step = 150;
                if(x > 100) x = (x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
            }
            if (e.key.keysym.sym == SDLK_RIGHT){
                step = 150;
                if(x < 450) x = (x + step) % SCREEN_WIDTH;
            }
            if (e.key.keysym.sym == SDLK_DOWN){
                step = 80;
                if(y != 630) y = (y + step) % SCREEN_HEIGHT;
            }
            if (e.key.keysym.sym == SDLK_UP){
                step = 80;
                if(y > 100) y = (y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
            }

            // Xoá toàn bộ màn hình và vẽ lại
            refreshScreen(window,image, renderer,x,y,w,h);
        }
    }

    quitSDL(window, renderer);
    return 0;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
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
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), trong khi
* giữ nguyên chiều rộng và cao của ảnh
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
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

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), với
* chiều rộng và cao mới
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
* @param w: chiều rộng (mới)
* @param h: độ cao (mới)
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
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

// Xoá và vẽ lại toàn bộ màn hình với 1 hình chữ nhật
void refreshScreen(SDL_Window* window, SDL_Texture *tex, SDL_Renderer* renderer, int x, int y, int w, int h)
{
    // Đặt màu vẽ thành xanh lam (blue), xoá màn hình về màu xanh lam.
    SDL_Texture *background = loadTexture("road2.bmp", renderer);
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //SDL_RenderClear(renderer);

    // Đặt màu vẽ về trắng và vẽ hình chữ nhật
    SDL_Texture *image = loadTexture("black.bmp", renderer);
    SDL_Texture *linken = loadTexture("linken.bmp",renderer);
    SDL_Texture *regen = loadTexture("regen.bmp",renderer);
    renderTexture(image, renderer, x, y, w, h);
    renderTexture(linken, renderer, 35, 100, 80, 80);
    renderTexture(regen, renderer, 35+150, 100, 80, 80);
    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}


//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
//**************************************************************

