#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;

	loadTexture(filepath);

	this->width = image->w;
	this->height = image->h;
	this->pivotX = image->w/2;
	this->pivotY = image->h/2;

}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject(){
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);
	
}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys){
	
}

double distance(SDL_Point a, SDL_Point b){
	return sqrt(pow((b.y - a.y), 2) + pow((b.x - a.x), 2));
}

void DisplayObject::draw(AffineTransform &at){

	// Apply transformations
	if(curTexture != NULL && isVisible){
		at.translate(posX, posY);
		at.scale(scaleX, scaleY);
		at.rotate(rotation % 360);
		at.translate(-pivotX, -pivotY);

		// Get global coordinates from the local image corner coordinates.
		SDL_Point ul = at.transformPoint(0, 0);
		SDL_Point ur = at.transformPoint(image->w, 0);
		SDL_Point ll = at.transformPoint(0, image->h);
		SDL_Point lr = at.transformPoint(image->w, image->h);

		SDL_Point pivot;
		pivot.x = 0;
		pivot.y = 0;

		double angle = atan2(ur.y - ul.y, ur.x - ul.x) * (180.0/M_PI);	// thnx wyatt

		// Perform draws
		SDL_Rect dstrect = { ul.x , ul.y , (int)distance(ul, ur), (int)distance(ul, ll)};
		SDL_SetTextureAlphaMod(curTexture, alpha);		
																  // rotate angle and rotate point
		SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, angle, &pivot, SDL_FLIP_NONE);
		// Revert transformations
		at.translate(pivotX, pivotY);
		at.rotate(-(rotation % 360));
		at.scale(1/scaleX, 1/scaleY);
		at.translate(-posX, -posY);
	}

}