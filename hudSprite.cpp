#include "hudSprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "viewport.h"

void HudSprite::myUpdate(int count,Uint32 ticks){
	update(ticks);
	advanceFrame(count);
}

void HudSprite::advanceFrame(int count) {
	if (count >= 1){
		currentFrame = count - 1;
   }else{
		currentFrame = 7;
	}
}

HudSprite::HudSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"X"), 
                    Gamedata::getInstance().getXmlInt(name+"Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"SpeedY"))
           ),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),

  currentFrame(7),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"Frames") ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

HudSprite::HudSprite(const HudSprite& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

void HudSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(Viewport::getInstance().X());
  Uint32 y = static_cast<Uint32>(Viewport::getInstance().Y());
  frames[currentFrame]->draw(x+305, y+95);
}

void HudSprite::update(Uint32 ticks) { 
  if(ticks){}
  //Vector2f incr = getVelocity() * static_cast<float>(ticks)*0.001;
  //setPosition(getPosition()+incr);
  return;
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  

}
