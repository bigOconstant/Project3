#ifndef _Hud_h_
#define _Hud_h_

#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"
#include "hudSprite.h"

class Clock;

class Hud{
	public:
		Hud(Clock&);
		void draw() const;
		void update(Uint32);
		void reset() { health = 8; lives = 3;}
		void swapShown() { isShown = !isShown;}
		void lostHealth();
	private:
		SDL_Surface *screen;
		Clock& clock;
		HudSprite heart;
		Vector2f topLeft,botRight;
		bool isShown;
		int health;
		int lives;
		const Uint32 RED;
		const Uint32 GREEN;
		const Uint32 BLUE;
		const Uint32 BLACK;
		const Uint32 WHITE;
		
		void setUp() const;

		Hud(const Hud&);
		Hud& operator=(const Hud&);
};

#endif
