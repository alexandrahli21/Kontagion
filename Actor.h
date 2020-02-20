#ifndef ACTOR_H_
#define ACTOR_H_

#include <set>
#include <cmath>
#include <valarray>
#include "GraphObject.h"
#include "GameWorld.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject 
{
public:
	Actor(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world, bool damageable);
	
	//virtual int init();
	//virtual int move();
	virtual void doSomething() = 0;
	StudentWorld* getWorld() const;
	//virtual ~Actor();
private:
	StudentWorld* m_world;
	bool m_dead;
	bool m_damageable;
};


class Socrates : public Actor 
{
public:
	Socrates(StudentWorld* world);
	virtual void doSomething();
private:
};

class Dirt : public Actor 
{
public: 
	Dirt(double startX, double startY, StudentWorld* world);

	virtual void doSomething(); 
private:
	
};

#endif // ACTOR_H_