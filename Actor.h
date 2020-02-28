#ifndef ACTOR_H_
#define ACTOR_H_

#include <set>
#include <list>
#include <string>
#include <cmath>
#include <valarray>
#include "GraphObject.h"
#include "GameWorld.h"
#include "GameConstants.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject 
{
public:
	Actor(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
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
	bool m_dead;
};


class Dirt : public Actor 
{
public: 
	Dirt(double startX, double startY, StudentWorld* world);
	virtual void doSomething(); 
	virtual bool takeDamage(int);
	virtual bool blocksBacteriumMovement() const;
};
class Food : public Actor
{
public:
	Food(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual bool isEdible() const;
};
class Pit : public Actor
{
public:
	Pit(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual bool preventsLevelCompleting() const;
private: 
	int m_numRS, m_numAS, m_numEColi;
};

class Agent : public Actor
{
public:
	Agent(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world, int hitPoints);
	virtual bool takeDamage(int damage);
	int numHitPoints() const;
	void restoreHealth(); 
	virtual int soundWhenHurt() const = 0; 
	virtual int soundWhenDie() const = 0; 
private: 
	int m_numHP;
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

class Bacterium : public Agent
{
public:
	Bacterium(int imageID, double startX, double startY, StudentWorld* world, int hitPoints);
	virtual bool takeDamage(int damage);
	virtual bool preventsLevelCompleting() const;
};

class EColi : public Bacterium
{
public:
	EColi(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual int soundWhenHurt() const;
	virtual int soundWhenDie() const;
};

class Salmonella : public Bacterium
{
public:
	Salmonella(double startX, double startY, StudentWorld* world, int hitPoints);
	virtual int soundWhenHurt() const;
	virtual int soundWhenDie() const;
};

class RegularSalmonella : public Salmonella
{
public:
	RegularSalmonella(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
private:
	int m_foodEaten;
};

class AggressiveSalmonella : public Salmonella
{
public:
	AggressiveSalmonella(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
};

#endif // ACTOR_H_