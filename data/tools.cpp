#include "tools.h"
#include "prepare.h"
#include <map>
#include <vector>
#include "../vendor/tinydir.h"

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


// bool loadGraphics(std::map<std::string, SDL_Texture*> gfxMap)
// {
//     // split filename . ext
//     // iterate over them, loading each one as a texture and storing it in the map
//     std::string gfxPath = "resources/graphics/";
//
//     std::map<std::string, SDL_Texture*> gfx;
//     tinydir_dir gfxDir;
//     tinydir_open(&gfxDir, gfxPath.c_str());
//
//     while (gfxDir.has_next)
//     {
//       tinydir_file file;
//       tinydir_readfile(&gfxDir, &file);
//
//       std::cout << file.name;
//       if (file.is_dir)
//       {
//         // call function recursively with new dir
//         std::cout << "/";
//
//         tinydir_dir gfxSubDir;
//         std::string gfxSubPath = gfxPath + file.name + "/";
//
//         // function begins here at open
//         tinydir_open(&gfxSubDir, gfxSubPath.c_str());
//
//
//         tinydir_next(&gfxDir);
//         continue;
//       }
//       std::cout << std::endl;
//
//       std::string individualPath = gfxPath + file.name;
//       //std::cout << individualPath << std::endl;
//
//       SDL_Texture* img = nullptr;
//       img = loadTexture(individualPath);
//       if (img == NULL)
//       {
//         std::cout << "Failed to load texture!" << std::endl;
//       }
//
//
//       tinydir_next(&gfxDir);
//     }
//
//     tinydir_close(&gfxDir);
//
//     return true; // change this later
// }


bool mapResourceNode(std::string path, std::vector<std::string>& paths) {

  tinydir_dir dir;
  tinydir_open(&dir, path.c_str());

  while (dir.has_next)
  {
    tinydir_file file;
    tinydir_readfile(&dir, &file);
    std::cout << file.name << std::endl;

    if (strlen(file.name) > 2) // directories need to be > 2 chars long
    {
      if (file.is_dir)
      {
        mapResourceNode(path+file.name+"/", paths);
      } else
      {
        paths.push_back(path+file.name);
      }
    }

    tinydir_next(&dir);
  }

  return true;
}

bool loadGraphics(std::map<std::string, SDL_Texture*> map) {
  std::vector<std::string> paths;
  mapResourceNode("resources/graphics/", paths);

  std::cout << "\n\n---------------\n\n" << std::endl; //debug


  for (auto &path: paths) {
    std::cout << path << std::endl;  //debug
    SDL_Texture* img = nullptr;
    img = loadTexture(path);
    if (img == NULL)
    {
      std::cout << "Failed to load texture: " << path << std::endl;
    } else
    {
      map[path] = img;
    }
  }
  return true;
}
