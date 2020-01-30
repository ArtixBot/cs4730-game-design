#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"


using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	
	DisplayObjectContainer* sun;
	DisplayObjectContainer* planet_1;
	DisplayObjectContainer* planet_2;
	DisplayObjectContainer* moon_1;
	DisplayObjectContainer* moon_2;
};

#endif