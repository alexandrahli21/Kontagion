#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>


Actor::Actor(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world)
	: GraphObject(imageID, startX, startY, dir, depth), m_world(world),  m_type(imageID) {}


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
	:Actor(IID_DIRT, startX, startY, 0, 1, world) {}

void Dirt::doSomething() //do nothing every tick
{
	//if a spray/flame hits dirt, both spray/flame and dirt will diappear 
	//blocks aall movement of bavteria 
	//blocks movement of all spray and flames
}

bool Dirt::takeDamage(int)
{
	return true; //dummy code
}

bool Dirt::blocksBacteriumMovement() const {
	return true;
}


Pit::Pit(double startX, double startY, StudentWorld* world)
	:Actor(IID_PIT, startX, startY, 0, 1, world) {}

void Pit::doSomething()
{
}

bool Pit::preventsLevelCompleting() const
{
	return false; //dummy code
}

Food::Food(double startX, double startY, StudentWorld* world)
	:Actor(IID_FOOD, startX, startY, up, 1, world) {}

void Food::doSomething() {
	//does nothing 
	//cannot be damaged by spray/flames
	//doesn't block movement of bacteria
}

bool Food::isEdible() const {
	return true;
}


Agent::Agent(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world, int hitPoints)
	:Actor(imageID, startX, startY, dir, depth, world)  {}

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
	:Agent(IID_PLAYER, startX, startY, 0, 0, world, 100) {}

void Socrates::doSomething() {
	//if (numHitPoints() <= 0)
	//	return; 

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

	if (numSprays() < 20) {
		//increase available number of spray by 1 spray
		//wait 1+ ticks without spraying to replenish his spray charges
	}
}

int Socrates::soundWhenHurt() const {
	return SOUND_PLAYER_HURT;
}

int Socrates::soundWhenDie() const {
	return SOUND_PLAYER_DIE;
}

// Increase the number of flamethrower charges the object has.
void Socrates::addFlames() {

}

// How many flamethrower charges does the object have?
int Socrates::numFlames() const 
{ 
	return 5; //starts out w 5
}

// How many spray charges does the object have?
int Socrates::numSprays() const {
	return 0; //dummy
}

Bacterium::Bacterium(int imageID, double startX, double startY, StudentWorld* world, int hitPoints)
	:Agent(imageID, startX, startY, 0, up, world, hitPoints) {}

bool Bacterium::takeDamage(int damage) {
	return true; //dummy code
}

bool Bacterium::preventsLevelCompleting() const {
	return false; //dummy code
}

EColi::EColi(double startX, double startY, StudentWorld* world)
	:Bacterium(IID_ECOLI, startX, startY, world, 5) {}


void EColi::doSomething() {
	//
}

int EColi::soundWhenHurt() const {
	return SOUND_ECOLI_HURT;
}

int EColi::soundWhenDie() const {
	return SOUND_ECOLI_DIE;
}