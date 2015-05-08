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

void close(std::map<std::string, SDL_Texture*> gfx,
           std::map<std::string, Mix_Music*> music,
           std::map<std::string, TTF_Font*> fonts)
{

  // Destroy gfx
  for (auto &img: gfx)
  {
    SDL_DestroyTexture(img.second);
    img.second = nullptr;
  }

  // Destroy music
  for (auto &track: music)
  {
    Mix_FreeMusic(track.second);
    track.second = nullptr;
  }

  // Destroy fonts
  for (auto &font: fonts)
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

  // all of this needs to go into a loadMedia function or something
  std::map<std::string, Mix_Music*> music;
  Tools::loadMusic(music);

  std::map<std::string, SDL_Texture*> gfx;
  Tools::loadGraphics(gfx);

  std::map<std::string, TTF_Font*> fonts;
  Tools::loadFonts(fonts);

  Tools::Sprite testGuy;
  if( !testGuy.setImage( gfx["foo.png"] ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
  }

  Tools::Sprite testText;
  SDL_Color textColor = {0x20,0x0F,0xA0};
  if (!testText.setImageFromText("helloooooooooo world", textColor, fonts["Fixedsys500c.ttf"]))
  {
    printf("Failed to render text!\n");
  }

  Tools::Sprite testGirl;
  if( !testGirl.setImage( gfx["sarn.png"] ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
  }

  testGirl.setBlendMode(SDL_BLENDMODE_BLEND);
  // --------------------------------------------------------------

  bool quit = false;
  SDL_Event e;

  Uint8 alpha = 255;

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
            if (Mix_PlayMusic(music["koorong.wav"], -1) == -1)
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
    SDL_RenderCopy(Screen::renderer, gfx["splash2.png"], NULL, NULL );
    testGuy.render(0, 0);
    testText.render( ( Constants::SCREEN_W - testText.getWidth() ) / 2, ( Constants::SCREEN_H - testText.getHeight() ) / 2 );
    testGirl.setAlpha(alpha);
    testGirl.render(0,0);

    // Update screen
    SDL_RenderPresent(Screen::renderer);

  } // main loop


  // instantiate control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close(gfx, music, fonts);
  return 0;
}
