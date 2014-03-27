#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"

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
  World world1,world2;
  Viewport& viewport;
  Hud hud;

  std::vector<Drawable*> sprites;
  std::vector<Drawable*> sprites2;
	std::vector<Drawable*> shootingStars;

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
