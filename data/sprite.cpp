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

bool Tools::Sprite::setImageFromText( std::string textureText, SDL_Color textColor, TTF_Font* font ) //shim
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface( Screen::renderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
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

void Tools::Sprite::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
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
