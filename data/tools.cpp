#include "tools.h"
#include "prepare.h"
#include <vector>
#include "../vendor/tinydir.h"
#include "sprite.h"

//debug
#include <iostream>

SDL_Texture* loadTexture(std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(Screen::renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}


bool mapResourceNode(std::string path, std::map<std::string, std::string>& paths) {

  tinydir_dir dir;
  tinydir_open(&dir, path.c_str());

  while (dir.has_next)
  {
    tinydir_file file;
    tinydir_readfile(&dir, &file);

    if (strlen(file.name) > 2) // directories need to be > 2 chars long
    {
      if (file.is_dir)
      {
        mapResourceNode(path+file.name+"/", paths);
      } else
      {
        paths[file.name] = path+file.name;
      }
    }

    tinydir_next(&dir);
  }

  return true;
}

bool Tools::loadGraphics() {

  std::map<std::string, std::string> paths;
  mapResourceNode("resources/graphics/", paths);

  for (auto &path: paths) {
    SDL_Texture* img = nullptr;
    img = loadTexture(path.second);
    if (img == NULL)
    {
      std::cout << "Failed to load texture: " << path.second << std::endl;
    } else
    {
      Tools::gfx[path.first] = img;
    }
  }

  return true;
}


bool Tools::loadMusic() {

  std::map<std::string, std::string> paths;
  mapResourceNode("resources/music/", paths);

  for (auto &path: paths) {
    Mix_Music* file = nullptr;
    file = Mix_LoadMUS(path.second.c_str());
    if (file == NULL)
    {
      std::cout << "Failed to load music: " << path.second << std::endl;
    } else
    {
      Tools::music[path.first] = file;
    }
  }

  return true;
}


bool Tools::loadFonts() {

  std::map<std::string, std::string> paths;
  mapResourceNode("resources/fonts/", paths);

  for (auto &path: paths) {
    TTF_Font* font = nullptr;
    font = TTF_OpenFont(path.second.c_str(), 28);
    if (font == NULL)
    {
      std::cout << "Failed to load font: " << path.second << std::endl;
    } else
    {
      Tools::fonts[path.first] = font;
    }
  }

  return true;
}

std::map<std::string, Mix_Music*> Tools::music;
std::map<std::string, SDL_Texture*> Tools::gfx;
std::map<std::string, TTF_Font*> Tools::fonts;

bool Tools::loadMedia() {
  Tools::loadMusic();
  Tools::loadGraphics();
  Tools::loadFonts();

  return true;
}
