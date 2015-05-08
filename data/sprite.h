#ifndef SPRITE_H
#define SPRITE_H

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <iostream>

namespace Tools {
  class Sprite
  {
      public:
          Sprite();
          ~Sprite();

          // All the resources in the game are pre-loaded into maps so
          // change all the loadFoo..s to setters
          //Loads image at specified path
          bool loadFromFile( std::string path );
          //Creates image from font string
          // bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

          //Deallocates texture
          void free();

          // void setColor( Uint8 red, Uint8 green, Uint8 blue );
          // void setBlendMode( SDL_BlendMode blending );
          // void setAlpha( Uint8 alpha );

          //Renders texture at given point
          void render( int x, int y );//SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

          //Gets image dimensions
          int getWidth();
          int getHeight();

      private:
          // Actual image
          SDL_Texture* mTexture;
          int mWidth;
          int mHeight;
  };
}
#endif
