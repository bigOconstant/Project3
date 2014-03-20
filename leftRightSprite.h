#ifndef _H_LEFTRIGHTSPRITE
#define _H_LEFTRIGHTSPRITE
#include <string>
#include <vector>
#include "drawable.h"

class LeftRightSprite : public Drawable {
public:
  LeftRightSprite(const std::string&);
  LeftRightSprite(const LeftRightSprite&);
  virtual ~LeftRightSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned numberOfSets;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
};
#endif
