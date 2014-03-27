#ifndef FALLINGSPRITE__H
#define FALLINGSPRITE__H
#include <string>
#include "drawable.h"

class FallingSprite : public Drawable {
public:
  FallingSprite(const std::string&);
  FallingSprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
  FallingSprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  FallingSprite(const FallingSprite& s);
  virtual ~FallingSprite() { } 
  FallingSprite& operator=(const FallingSprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void setPainter(float s){
    painter = true;
    size = s;
  }
  virtual void update(Uint32 ticks);

  float getSize() const{return size;}

  

private:
  float size;
  bool painter;
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const FallingSprite*) const;
};
#endif
