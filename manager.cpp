#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "twowaysprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
//#include "vector2f.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  for (unsigned i = 0; i < sprites2.size(); ++i) {
    delete sprites2[i];
  }
  /*
  for (unsigned i = 0; i < ransprites.size(); ++i) {
    delete ransprites[i];
  }*/
   delete character;
   delete grass;
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("back", Gamedata::getInstance().getXmlInt("backFactor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  sprites2(),
  character(),
  grass(),
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


Vector2f vel(10,0);
  for(int i = 0; i <100; ++i){
  //Sprite temp("whitestar");
  Vector2f pos((rand() % 2500) ,(rand() % 1219) );
  //temp.setPosition(pos);
  sprites2.push_back((new Sprite("whitestar")));
  sprites2[i]->setPosition(pos);
  //sprites2[i]->setVelocity(vel);

  }

  sprites.push_back( new Sprite("moon"));
  //sprites.push_back(new Sprite("mountains"));
  sprites.push_back(new Sprite("ground"));
  

  sprites.push_back(new Sprite("tree"));
  //  sprites.push_back(new Sprite("grass")); 

  //sprites2.push_back(new Sprite("grass"));
  character = new twowaysprite("wolf"); 
  grass = new Sprite("grass");

  // sprites.push_back(new twowaysprite("wolf"));
  //sprites.push_back( new Sprite("star") );
  //std::cout<<"size of sprite with two sprites = "<< sprites.size()<<std::endl;
  //sprites.push_back( new Sprite("greenorb") );

  viewport.setObjectToTrack(character);

}

void Manager::draw() const {
  world.draw();
 /* 
 
  for (unsigned i = 0; i < sprites2.size(); ++i) {
   sprites2[i]->draw();
  }
 */
  for (unsigned i = 0; i < sprites.size(); ++i) {
   sprites[i]->draw();
  }
  character->draw();
  grass->draw();

  io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
  io.printMessageValueAt("fps: ", clock.getAvgFps(), 10, 40);
  io.printMessageAt("Press T to switch sprites", 10, 70);
  io.printMessageAt(title, 10, 460);
  viewport.draw();

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
  /*
  for (unsigned int i = 0; i < sprites2.size(); ++i) {
    sprites2[i]->update(ticks);
  }
  */
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }

  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  character->update(ticks);
  grass->update(ticks);
  world.update();
  viewport.update(); // always update viewport last
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
	
	if (keystate[SDLK_UP] && !keyCatch) {
          keyCatch = true;
	  character->jump();
        }
	
    }

    draw();
    update();
  }
}
