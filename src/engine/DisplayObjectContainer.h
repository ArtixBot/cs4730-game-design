#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include <vector>
#include "DisplayObject.h"
#include "AffineTransform.h"
// #include "Event.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObjectContainer : public DisplayObject{

public:
	
	DisplayObjectContainer();
	DisplayObjectContainer(string id, string filepath);
	DisplayObjectContainer(string id, int red, int green, int blue);
	virtual ~DisplayObjectContainer();

	void addChild(DisplayObject* child);
	void addChild(DisplayObject* child, int offsetX, int offsetY);	// with offset
	void removeImmediateChild(DisplayObject* child);
	void removeImmediateChild(string id);
	void removeChild(int index);
	void removeThis();

	virtual int numChildren();
	virtual DisplayObject* getChild(int index);
	virtual DisplayObject* getChild(string id);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	virtual void setOffset(int offsetX, int offsetY);

	vector<DisplayObject*> children;
private:
	
	
};

#endif