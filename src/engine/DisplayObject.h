#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObject{

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red,green,blue;
	string type = "DisplayObject";

	bool isRGB = false;
	bool isVisible = true;

	int width;
	int height;

	int posX = 0; int posY = 0;
	int pivotX = 0; int pivotY = 0;
	double scaleX = 1.0; double scaleY = 1.0;
	int rotation = 0;
	int alpha = 255;	// ranges from 0-255 for SDL_SetTextureAlphaMod; 255 = opaque, 0 = transparent
	string parent;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

private:
	
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;

};

#endif