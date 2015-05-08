# multiscene-template-Cpp-SDL
This is basically a C++/SDL implementation of Mekire's multiscene template for Pygame (https://github.com/Mekire/pygame-mutiscene-template-with-movie).  

It is currently incomplete.  

Only verified to compile on OS X Yosemite 10.10.3  
`g++ -g -o foo.out main.cpp data/*.cpp $(sdl2-config --libs --cflags) -lSDL2_Image -lSDL2_Mixer - lSDL2_Ttf -std=c++0x`
