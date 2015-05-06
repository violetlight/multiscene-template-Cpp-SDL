#include "tools.h"
#include "prepare.h"

SDL_Texture* loadTexture(std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(Screen::renderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

SDL_Texture* loadGraphics()
{
    SDL_Texture* gfx = nullptr;
    //Load PNG texture
    gfx = loadTexture("resources/graphics/splash2.png");
    // gfx = loadTexture("splash1ss.png");
    if(gfx == NULL)
    {
        printf("Failed to load texture image!\n");
    }

    return gfx;
}
