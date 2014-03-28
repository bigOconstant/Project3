#ifndef _H_HUDSPRITE
#define _H_HUDSPRITE
#include <string>
#include <vector>
#include "drawable.h"

class HudSprite : public Drawable {
public:
  HudSprite(const std::string&);
  HudSprite(const HudSprite&);
  virtual ~HudSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  virtual void setPainter(float size){if(size){};}

  void myUpdate(int count,Uint32 ticks);
	void lostHealth() {currentFrame--;}
protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  int frameWidth;
  int frameHeight;

  void advanceFrame(int count);
};
#endif
