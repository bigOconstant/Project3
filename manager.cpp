#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

#include "multisprite.h"
#include "leftRightSprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"


Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  for(unsigned i =0; i < fallingStars.size(); ++i){
    delete fallingStars[i];
  }
   delete character;
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  sky("sky", Gamedata::getInstance().getXmlInt("skyFactor") ),
  ground("ground", Gamedata::getInstance().getXmlInt("groundFactor") ),
  grass("grass", Gamedata::getInstance().getXmlInt("grassFactor") ),
  viewport( Viewport::getInstance() ),hud(clock),
  sprites(),fallingStars(),
  character(),
  currentSprite(2),
  
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);

  sprites.reserve(2);
  sprites.push_back( new Sprite("moon"));
  sprites.push_back(new Sprite("tree"));

  fallingStars.reserve(10);
  std::vector<float> fallingStarSizes;
  fallingStarSizes.reserve(10);
  for(int i=0; i < 10; i++){
    float tempSize = (rand() % 100) + 1;
    fallingStarSizes.push_back(tempSize);
  }
  sort(fallingStarSizes.begin(),fallingStarSizes.end());

  for(int i = 0; i < 10; i++){
    fallingStars.push_back(new FallingSprite("shooting_star"));
    fallingStars[i]->setPainter(fallingStarSizes[i]);
    fallingStars[i]->setPosition(Vector2f((rand() % 2500),(rand() % 1219)));
    fallingStars[i]->setVelocity(Vector2f(-(rand() % 25)-25,(rand() % 121)));
  }

  character = new LeftRightSprite("wolf"); 

  viewport.setObjectToTrack(character);

}

void Manager::draw() const {
  sky.draw();
  sprites[0]->draw(); //moon
  /*for(int i = 0; i < 5; i++){
    fallingStars[i]->draw();
  }*/
  ground.draw();
  sprites[1]->draw(); //tree
  character->draw(); //wolf
  /*for(int i = 5; i < 10; i++){
    fallingStars[i]->draw();
  }*/
  grass.draw();

  io.printMessageAt(title, 10, 460);
  viewport.draw();
  hud.draw();

  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "video/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();

  for (unsigned int i = 0; i < fallingStars.size(); ++i) {
    fallingStars[i]->update(ticks);
  }

  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  sky.update();
  sprites[0]->update(ticks); //moon
  ground.update();
  sprites[1]->update(ticks); //tree
  character->update(ticks);
  grass.update();
  viewport.update(); // always update viewport last
  hud.update(ticks);
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( not done ) {

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      if (keystate[SDLK_t] && !keyCatch) {
        keyCatch = true;
        currentSprite = (currentSprite+1) % sprites.size();
        //if (currentSprite == 1)
        //  currentSprite = 2;
        viewport.setObjectToTrack(sprites[currentSprite]);
      }
      if (keystate[SDLK_s] && !keyCatch) {
        keyCatch = true;
        clock.toggleSloMo();
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if (keystate[SDLK_F4] && !makeVideo) {
        std::cout << "Making video frames" << std::endl;
        makeVideo = true;
      }
	    if (keystate[SDLK_F1] && !keyCatch) {
			  keyCatch = true;
        hud.swapShown();
      }
      if (keystate[SDLK_h] && !keyCatch) {
	 		  keyCatch = true;
        hud.lostHealth();
      }
	     /*if (keystate[SDLK_UP] && !keyCatch) {
          keyCatch = true;
	       character->jump();
        }*/
	
    }

    draw();
    update();
  }
}
