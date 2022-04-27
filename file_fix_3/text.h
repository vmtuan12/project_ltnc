#ifndef TEXT_H
#define TEXT_H

#include "function.h"

class textObj
{
	public:
		//Initializes variables
		textObj();

		//Deallocates memory
		~textObj();

		//Loads image at specified path
		bool loadFromFile(const std::string &path);

		//Creates image from font string
		bool loadFromRenderedText(const std::string &textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void renderText(const int &x,const int &y, SDL_Rect* clip,const double &angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer *gRenderer);

		//Gets image dimensions
		int getWidth() {return mWidth;}
		int getHeight() {return mHeight;}

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif // TEXT_H
