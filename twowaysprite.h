#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class twowaysprite : public Drawable {
public:
  twowaysprite(const std::string&);
  twowaysprite(const twowaysprite&);
  virtual ~twowaysprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  void jump();

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
};
#endif
