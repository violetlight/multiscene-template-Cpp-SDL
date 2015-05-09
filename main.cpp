#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <sdl2/SDL_mixer.h>
#include <sdl2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "data/prepare.h"
#include "data/tools.h"
#include "data/constants.h"
#include "data/sprite.h"
#include <iostream>

void close()
{

  // Destroy gfx
  for (auto &img: Tools::gfx)
  {
    SDL_DestroyTexture(img.second);
    img.second = nullptr;
  }

  // Destroy music
  for (auto &track: Tools::music)
  {
    Mix_FreeMusic(track.second);
    track.second = nullptr;
  }

  // Destroy fonts
  for (auto &font: Tools::fonts)
  {
    TTF_CloseFont(font.second);
    font.second = nullptr;
  }

  // Destroy window
  SDL_DestroyRenderer(Screen::renderer);
  SDL_DestroyWindow(Screen::window);
  Screen::window = nullptr;
  Screen::renderer = nullptr;

  // Quit SDL subsystems
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}



int main (int argc, char* args[])
{

  Prepare::init();
  Tools::loadMedia();


  Tools::Sprite testText;
  SDL_Color textColor = {0x20,0x0F,0xA0};
  if (!testText.setImageFromText("helloooooooooo world", textColor, Tools::fonts["Fixedsys500c.ttf"]))
  {
    printf("Failed to render text!\n");
  }

  Tools::Sprite testGirl;
  if( !testGirl.setImage( Tools::gfx["sarn.png"] ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
  }

  testGirl.setBlendMode(SDL_BLENDMODE_BLEND);

  int WALKING_ANIMATION_FRAMES = 4;
  SDL_Rect walkingClips[WALKING_ANIMATION_FRAMES];
  Tools::Sprite walkingSpriteSheet;
  if( !walkingSpriteSheet.setImage( Tools::gfx["foo.png"] ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
  }
  else
  {
    //Set sprite clips
    walkingClips[ 0 ].x =   0;
    walkingClips[ 0 ].y =   0;
    walkingClips[ 0 ].w =  64;
    walkingClips[ 0 ].h = 205;

    walkingClips[ 1 ].x =  64;
    walkingClips[ 1 ].y =   0;
    walkingClips[ 1 ].w =  64;
    walkingClips[ 1 ].h = 205;

    walkingClips[ 2 ].x = 128;
    walkingClips[ 2 ].y =   0;
    walkingClips[ 2 ].w =  64;
    walkingClips[ 2 ].h = 205;

    walkingClips[ 3 ].x = 196;
    walkingClips[ 3 ].y =   0;
    walkingClips[ 3 ].w =  64;
    walkingClips[ 3 ].h = 205;
  }

  bool quit = false;
  SDL_Event e;

  // debug, experimental, whatever
  Uint8 alpha = 255;
  int frame = 0;

  while(!quit)
  {
    while(SDL_PollEvent(&e) != 0)
    {

      // Key press
      if (e.type == SDL_KEYDOWN)
      {

        // Music-related
        if (e.key.keysym.sym == SDLK_9)
        {    // no music playing
          if (Mix_PlayingMusic() == 0)
          {    // then play it
            if (Mix_PlayMusic(Tools::music["koorong.wav"], -1) == -1)
            {  // error
              return 1;
            } // music is playing
          } else
          {
            if (Mix_PausedMusic() == 1)
            {
              Mix_ResumeMusic();
            } else
            {
              Mix_PauseMusic();
            }
          }
        }

        // Increase alpha on w
        else if (e.key.keysym.sym == SDLK_w)
        {
          if (alpha+32 > 255)
          {
            alpha = 255;
          }

          else
          {
            alpha += 32;
          }
        }

        // Decrease alpha on s
        else if (e.key.keysym.sym == SDLK_s)
        {
          if (alpha-32 < 0)
          {
            alpha = 0;
          }

          else
          {
            alpha -= 32;
          }
        }

      }

      // Quit event
      if(e.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    // Clear screen
    SDL_SetRenderDrawColor(Screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(Screen::renderer);

    // Render splash image
    SDL_RenderCopy(Screen::renderer, Tools::gfx["splash2.png"], NULL, NULL );
    testText.render( ( Constants::SCREEN_W - testText.getWidth() ) / 2, ( Constants::SCREEN_H - testText.getHeight() ) / 2 );
    testGirl.setAlpha(alpha);
    testGirl.render(0,0);

    SDL_Rect* currentClip = &walkingClips[frame/4];
    int x = (Constants::SCREEN_W - currentClip->w) / 2;
    int y = (Constants::SCREEN_H - currentClip->h) / 2;
    walkingSpriteSheet.render(x, y, currentClip);

    // Update screen
    SDL_RenderPresent(Screen::renderer);

    ++frame;
    if (frame/4 >= WALKING_ANIMATION_FRAMES)
    {
      frame = 0;
    }

  } // main loop


  // instantiate control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close();
  return 0;
}
