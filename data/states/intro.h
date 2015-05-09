#ifndef STATE_INTRO_H
#define STATE_INTRO_H

#include "../state.h"

class Intro : public State {

public:
  void processEvent(SDL_Event &e);
  void update();
  void draw();
};

#endif
