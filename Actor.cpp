#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>


Actor::Actor(int imageID, double startX, double startY, Direction dir, StudentWorld* world)
	: GraphObject(imageID, startX, startY, dir), m_world(world),  m_type(imageID) {}

int Actor::getType() const 
{ return m_type; }

bool Actor::isDead() const
{
	return false; //dummy code for rn
}

void Actor::setDead()
{
	
}

bool Actor::takeDamage(int damage) 
{
	return false; //dummy code
}

bool Actor::blocksBacteriumMovement() const
{
	return true; //dummy code
}

bool Actor::isEdible() const
{
	return false; //dummy code
}

bool Actor::preventsLevelCompleting() const
{
	return false; //dummy code
}

StudentWorld* Actor::getWorld() const
{ return m_world; }

Dirt::Dirt(double startX, double startY, StudentWorld* world)
	:Actor(IID_DIRT, startX, startY, 0, world) {}

void Dirt::doSomething() //do nothing every tick
{}

bool Dirt::takeDamage(int)
{
	return true; //dummy code
}

bool Dirt::blocksBacteriumMovement() const {
	return true;
}


Pit::Pit(double startX, double startY, StudentWorld* world)
	:Actor(IID_PIT, startX, startY, 0, world) {}

void Pit::doSomething()
{
}

bool Pit::preventsLevelCompleting() const
{
	return false; //dummy code
}



Agent::Agent(int imageID, double startX, double startY, Direction dir, StudentWorld* world, int hitPoints)
	:Actor(imageID, startX, startY, dir, world)  {}

bool Agent::takeDamage(int damage)
{
	return false; //dummy code
}

int Agent::numHitPoints() const
{
	return 0; //dummy code
}

void Agent::restoreHealth()
{
	//dummy code
}

Socrates::Socrates(double startX, double startY, StudentWorld* world)
	:Agent(IID_PLAYER, startX, startY, 0, world, 100) {} //might not be 100

void Socrates::doSomething() {
	int key;
	double leftX, leftY, rightX, rightY, theta;
	theta = atan2((getY()-128), (getX()-128));
	if (getWorld()->getKey(key)) {
		switch (key) {
		case KEY_PRESS_LEFT:
			leftX = (128 * (cos(theta + (pi / 36)))+128);
			leftY = (128 * (sin(theta  + (pi / 36)))+128);
			moveTo(leftX, leftY);
			setDirection(theta*360/(2*pi)+180);
			break;
		case KEY_PRESS_RIGHT:
			rightX = (128 * (cos(theta - (pi / 36)))+128);
			rightY = (128 * (sin(theta - (pi / 36)))+128);
			moveTo(rightX, rightY);
			setDirection(theta * 360 / (2 * pi) + 180);
			break;
		}
	}
}

int Socrates::soundWhenHurt() const {
	return 0; //dummy
}

int Socrates::soundWhenDie() const {
	return 0; //dummy
}

// Increase the number of flamethrower charges the object has.
void Socrates::addFlames() {

}

// How many flamethrower charges does the object have?
int Socrates::numFlames() const 
{ 
	return 0;
}

// How many spray charges does the object have?
int Socrates::numSprays() const {
	return 0; //dummy
}