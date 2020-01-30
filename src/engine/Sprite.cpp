#include "Sprite.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>

Sprite::Sprite(){

}

Sprite::Sprite(string id, string filepath) : DisplayObjectContainer(id, filepath){

}

Sprite::Sprite(string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue){
    
}

void Sprite::update(set<SDL_Scancode> pressedKeys){

}

void Sprite::draw(AffineTransform &at){

}