#include "sprite.h"
#include "prepare.h" // for access to Screen namespace, this is horirble

Tools::Sprite::Sprite()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Tools::Sprite::~Sprite()
{
	free();
}

bool Tools::Sprite::setImage( SDL_Texture* image )
{
	//Get rid of preexisting texture to allow switching
	free();

	int w, h;
	SDL_QueryTexture(image, NULL, NULL, &w, &h);
	//Get image dimensions
	mWidth = w;
	mHeight = h;

	//Return success
	mTexture = image;
	return mTexture != NULL;
}

void Tools::Sprite::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Tools::Sprite::render( int x, int y )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( Screen::renderer, mTexture, NULL, &renderQuad );
}

int Tools::Sprite::getWidth()
{
	return mWidth;
}

int Tools::Sprite::getHeight()
{
	return mHeight;
}
