#include "state.h"

State::State()
{
  startTime = 0.0;
  currentTime = 0.0;
  done = false;
  quit = false;
}

void State::startup(double currentTime) // would pass persist in...
{
  // ...and then unpack it here
  startTime = currentTime;
}


void State::cleanup()
{
  // the return type of this method would actually be the type of
  // the persist data bundle, which presents yet another problem.
  // perhaps templates would have to be used.
  done = false;
}
