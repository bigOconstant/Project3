#include <vector>
#include <SDL.h>

#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "leftRightSprite.h"
#include "sprite.h"
#include "hud.h"
#include "fallingSprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World sky,ground,grass;
  Viewport& viewport;
  Hud hud;

  std::vector<Drawable*> sprites;
  std::vector<FallingSprite*> fallingStars;
  LeftRightSprite *character;

  int currentSprite;

  bool makeVideo;
  int frameCount;
  std::string username;
  std::string title;
  int frameMax;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
