#ifndef ACTOR_H_
#define ACTOR_H_

#include <set>
#include <cmath>
#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject 
{
public:
	Actor(int imageID, double startX, double startY, Direction dir, int depth, double size)
		:GraphObject(imageID, startX, startY, dir, depth, size) {}
	virtual int init();
	virtual int move();
	//virtual ~Actor();
private:
	
};


class Socrates : public Actor 
{
public:
	Socrates()
		:Actor(IID_PLAYER, 0, (VIEW_HEIGHT/2), 0, 0, 1.0){}
private:
};

class Dirt : public Actor 
{
public: 
	Dirt(double startX, double startY)
		:Actor(IID_DIRT, startX, startY, 0, 1, 1.0) {}
	//virtual void doSomething(); //do nothing every tick
private:
	
};

#endif // ACTOR_H_