#include <SDL_ttf.h>

class State {

  double startTime;
  double currentTime;
  bool done;
  bool quit;
  State *next;
  State *previous;
  // persist needs to be some kind of map, but the data type is arbitrary
  // ??? persist;

public:
  virtual void processEvent(SDL_event &e);
  void startup(double currentTime);
  void cleanup();
  void update();
  //std::pair<
  // render_font needs to return a std::pair
}
