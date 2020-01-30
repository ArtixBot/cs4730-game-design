#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	sun = new DisplayObjectContainer("sun","./resources/sun/Idle_1.png");
	planet_1 = new DisplayObjectContainer("planet_1", "./resources/planet_1/Idle_1.png");
	planet_2 = new DisplayObjectContainer("planet_2", "./resources/planet_2/Idle_1.png");
	moon_1 = new DisplayObjectContainer("moon_1", "./resources/moon_1/Idle_1.png");
	moon_2 = new DisplayObjectContainer("moon_2", "./resources/moon_2/Idle_1.png");

	this->addChild(sun);
	sun->addChild(planet_1, 300, 0);
	sun->addChild(planet_2, -200, 100);
	planet_1->addChild(moon_1, -40, -40);
	planet_2->addChild(moon_2, 0, 205);
}

MyGame::~MyGame(){
	delete sun;
	delete planet_1;
	delete planet_2;
	delete moon_1;
	delete moon_2;
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	sun->rotation++;
	planet_1->rotation--;
	planet_2->rotation+= 2;
	for (std::set<SDL_Scancode>::iterator it = pressedKeys.begin(); it != pressedKeys.end(); ++it){

		switch(*it){
			// Translation
			case SDL_SCANCODE_LEFT:	// Left arrow key
				sun->posX -= 5;
				break;
			case SDL_SCANCODE_RIGHT:	// Right arrow key
				sun->posX += 5;
				break;
			case SDL_SCANCODE_UP:	// Up arrow key
				sun->posY -= 5;
				break;
			case SDL_SCANCODE_DOWN:	// Down arrow key
				sun->posY += 5;
				break;
			// Scaling
			case SDL_SCANCODE_Q:
				if (sun->scaleX > 0.2 && sun->scaleY > 0.2){	// max size 0.1
					sun->scaleX -= 0.1;
					sun->scaleY -= 0.1;
				}
				break;
			case SDL_SCANCODE_W:
				sun->scaleX += 0.1;
				sun->scaleY += 0.1;
				break;
			// Pivot Movement
			case SDL_SCANCODE_I:
				sun->pivotY-= 5;
				break;
			case SDL_SCANCODE_J:
				sun->pivotX-= 5;
				break;
			case SDL_SCANCODE_K:
				sun->pivotY+= 5;
				break;
			case SDL_SCANCODE_L:
				sun->pivotX+= 5;
				break;
			// Rotation
			case SDL_SCANCODE_A:
				sun->rotation++;
				break;
			case SDL_SCANCODE_S:
				sun->rotation-= 2;		// To future me: since at the start of update we're rotating++, we need -= 2 to counteract and rotate the other way by 1 degree (if -=1, we stay still).
				break;
			// Visibility
			case SDL_SCANCODE_P:
				isVisible = !isVisible;
				break;
			// Transparency
			case SDL_SCANCODE_Z:	// Fade in
				if (alpha < 250) { alpha += 5; }
				break;
			case SDL_SCANCODE_X:	// Fade out
				if (alpha > 5){ alpha -= 5; }
				break;
		}

	}
	// sun->update(pressedKeys);			// Possibly here? To be found out in an eventual time.
	// planet_1->update(pressedKeys);
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){

	SDL_RenderClear(Game::renderer);
	// sun->draw(at);
	Game::draw(at);
	// planet_1->draw(at);
	SDL_RenderPresent(Game::renderer);
}