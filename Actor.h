#ifndef ACTOR_H_
#define ACTOR_H_

#include <set>
#include <string>
#include <cmath>
#include <valarray>
#include "GraphObject.h"
#include "GameWorld.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject 
{
public:
	Actor(int imageID, double startX, double startY, Direction dir, StudentWorld* world);
	int getType() const;
	bool isDead() const;
	void setDead(); 
	virtual bool takeDamage(int damage);
	virtual bool blocksBacteriumMovement() const;
	virtual bool isEdible() const;
	virtual bool preventsLevelCompleting() const;
	virtual void doSomething() = 0;
	StudentWorld* getWorld() const;
private:
	StudentWorld* m_world;
	int m_type;
};


class Dirt : public Actor 
{
public: 
	Dirt(double startX, double startY, StudentWorld* world);
	virtual void doSomething(); 
	virtual bool takeDamage(int);
	virtual bool blocksBacteriumMovement() const;
};

class Pit : public Actor
{
public:
	Pit(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual bool preventsLevelCompleting() const;
};

class Agent : public Actor
{
public:
	Agent(int imageID, double startX, double startY, Direction dir, StudentWorld* world, int hitPoints);
	virtual bool takeDamage(int damage);
	int numHitPoints() const;
	void restoreHealth(); 
	virtual int soundWhenHurt() const = 0; 
	virtual int soundWhenDie() const = 0; 
};
	

class Socrates : public Agent
{
public:
	Socrates(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual int soundWhenHurt() const;
	virtual int soundWhenDie() const;
	void addFlames(); 
	int numFlames() const; 
	int numSprays() const;
};

#endif // ACTOR_H_