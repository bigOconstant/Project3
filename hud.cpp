#include "hud.h"
#include "clock.h"

Hud::Hud(Clock& c):
	screen(IOManager::getInstance().getScreen()),
	clock(c),heart("heart"),
	topLeft(Vector2f(20,120)),botRight(Vector2f(400,120)),
	isShown(false),health(8),lives(3),
	RED(SDL_MapRGB(screen->format,0xff,0x00,0x00)),
	GREEN(SDL_MapRGB(screen->format,0x00,0xff,0x00)),
	BLUE(SDL_MapRGB(screen->format,0x00,0x00,0xff)),
	BLACK(SDL_MapRGB(screen->format,0x00,0x00,0x00)),
	WHITE(SDL_MapRGBA(screen->format,0xff,0xff,0xff,100))
	{} 
void Hud::setUp() const{
	//hud background
	Draw_AALine(screen, topLeft[0], topLeft[1], botRight[0],topLeft[1],
		200.0,0x00,0x00,0xff,0xff/4);
	//hud outline
	//top line
	Draw_AALine(screen,topLeft[0]-2,topLeft[1]-100,botRight[0]+2,
		topLeft[1]-100,5.0,0x00,0x00,0x00,0xff/4);
	//bottom line
	Draw_AALine(screen,topLeft[0]-2,botRight[1]+100,botRight[0]+2,
		botRight[1]+100,5.0,0x00,0x00,0x00,0xff/4);
	//left line
	Draw_AALine(screen,topLeft[0],topLeft[1]-100,topLeft[0],
		botRight[1]+100,5.0,0x00,0x00,0x00,0xff/4);
	//right line
	Draw_AALine(screen,botRight[0],topLeft[1]-100,botRight[0],
		botRight[1]+100,5.0,0x00,0x00,0x00,0xff/4);
  IOManager::getInstance().
		printMessageValueAt("Seconds: ", clock.getSeconds(), 25, 25);
  IOManager::getInstance().
		printMessageValueAt("FPS: ", clock.getAvgFps(), 25, 45);
  IOManager::getInstance().
		printMessageAt("Press T to switch sprites", 25, 65);
	IOManager::getInstance().
		printMessageAt("Press H to simulate damage",25,85);
	IOManager::getInstance().
		printMessageAt("Press F1 to toggle the Hud",25,105);
  IOManager::getInstance().
		printMessageValueAt("Lives Left: ",lives,25, 125);
	IOManager::getInstance().
		printMessageValueAt("Score: ",clock.getSeconds()*50.0f,25,145);
	heart.draw();
}

void Hud::draw() const {
	if(isShown)
		setUp();
}

void Hud::update(Uint32 ticks){
	heart.myUpdate(health,ticks);
}

void Hud::lostHealth(){
	if(health == 1){
		if(lives == 0){
			reset();
		}else{
			health = 8;
			lives--;
		}
	}else if(health > 1){
		health--;
	}
}
