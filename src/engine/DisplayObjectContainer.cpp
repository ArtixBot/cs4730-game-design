#include "DisplayObjectContainer.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>

DisplayObjectContainer::DisplayObjectContainer() : DisplayObject(){
    this->children.clear();
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) : DisplayObject(id, filepath){}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id, red, green, blue){}

DisplayObjectContainer::~DisplayObjectContainer(){}

void DisplayObjectContainer::addChild(DisplayObject* child){
    this->children.push_back(child);
}

// Adds child and sets initial offset RELATIVE to the upper-left corner of the parent image.
void DisplayObjectContainer::addChild(DisplayObject* child, int offsetX, int offsetY){
    this->children.push_back(child);
    child->posX = offsetX;
    child->posY = offsetY;
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child){
    this->children.erase(std::remove(this->children.begin(), this->children.end(), child), this->children.end());
}

void DisplayObjectContainer::removeImmediateChild(string id){

}

void DisplayObjectContainer::removeChild(int index){
    this->children.erase(this->children.begin() + index);
}

void DisplayObjectContainer::removeThis(){  // ???
}

int DisplayObjectContainer::numChildren(){
    return this->children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index){
    return this->children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id){
    for (DisplayObject* child : this->children){
        if (child->id == id){
            return child;
        }
    }
    return NULL;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys){
    DisplayObject::update(pressedKeys);
}

void DisplayObjectContainer::draw(AffineTransform &at){
    DisplayObject::draw(at);

    at.translate(posX, posY);
    at.scale(scaleX, scaleY);
    at.rotate(rotation % 360);
    at.translate(-pivotX, -pivotY);

    for (DisplayObject* child : this->children){
        child->draw(at);
    }

    at.translate(pivotX, pivotY);
    at.rotate(-(rotation % 360));
    at.scale(1/scaleX, 1/scaleY);
    at.translate(-posX, -posY);
}

void DisplayObjectContainer::setOffset(int offsetX, int offsetY){
    DisplayObject::posX = offsetX;
    DisplayObject::posY = offsetY;
}