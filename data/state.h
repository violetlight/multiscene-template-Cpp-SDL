#ifndef STATE_H
#define STATE_H

#include <sdl2/SDL.h>

class State {

  double startTime;
  double currentTime;
  bool done;
  bool quit;
  std::string next; // these will be used as keys to index a map
  std::string previous;
  // persist needs to be some kind of map, but the data type is arbitrary
  // ??? persist;

public:
  State();
  ~State();
  void startup(double currentTime);
  void cleanup();
  virtual void processEvent(SDL_event &e);
  virtual void update();
  virtual void draw();
}

#endif
