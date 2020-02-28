#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;


Actor::Actor(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world)
	: GraphObject(imageID, startX, startY, dir, depth), 
		m_world(world),  m_type(imageID), m_dead(false) {}


bool Actor::isDead() const
{
	return m_dead; 
}

void Actor::setDead()
{
	m_dead = true;
}

bool Actor::takeDamage(int damage) 
{
	return false; //dummy code
}

bool Actor::blocksBacteriumMovement() const
{
	return false; 
}

bool Actor::isEdible() const
{
	return false; 
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
	:Actor(IID_PIT, startX, startY, 0, 1, world), m_numRS(5), m_numAS(3), m_numEColi(2) {}

void Pit::doSomething()
{
	if (m_numRS + m_numAS + m_numEColi <= 0) {
		setDead();
	}

	if (randInt(1, 50) == 2) {
		int totalBac = m_numRS + m_numAS + m_numEColi;
		int chance = randInt(1, totalBac); 
		if (1 <= chance <= m_numRS) {
			getWorld()->addActor(new RegularSalmonella(getX(), getY(), getWorld()));
			m_numRS--;
			getWorld()->playSound(SOUND_BACTERIUM_BORN);
		}
		if (m_numRS < chance <= m_numRS + m_numAS) {
			getWorld()->addActor(new AggressiveSalmonella(getX(), getY(), getWorld()));
			m_numAS--;
			getWorld()->playSound(SOUND_BACTERIUM_BORN);
		}
		if (m_numRS + m_numAS < chance <= totalBac) {
			getWorld()->addActor(new EColi(getX(), getY(), getWorld()));
			m_numEColi--;
			getWorld()->playSound(SOUND_BACTERIUM_BORN);
		}
	}
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
	:Actor(imageID, startX, startY, dir, depth, world), m_numHP(hitPoints) {}

bool Agent::takeDamage(int damage)
{
	m_numHP = m_numHP - damage; 
	return true;
}

int Agent::numHitPoints() const
{
	return m_numHP;
}

void Agent::restoreHealth()
{
	//dummy code
}

Socrates::Socrates(double startX, double startY, StudentWorld* world)
	:Agent(IID_PLAYER, startX, startY, 0, 0, world, 100) {}

void Socrates::doSomething() {
	if (numHitPoints() <= 0)
		return; 

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

Salmonella::Salmonella(double startX, double startY, StudentWorld* world, int hitPoints)
	 :Bacterium(IID_SALMONELLA, startX, startY, world, hitPoints) {}

int Salmonella::soundWhenHurt() const {
	return SOUND_SALMONELLA_HURT;
}

int Salmonella::soundWhenDie() const {
	return SOUND_SALMONELLA_DIE;
}

RegularSalmonella::RegularSalmonella(double startX, double startY, StudentWorld* world)
	:Salmonella(startX, startY, world, 4), m_foodEaten(0), m_movementPlan(0) {}

void RegularSalmonella::doSomething() {
	if (isDead()) {
		return;
	}

	if (getWorld()->getOverlappingSocrates(this) != nullptr) {
		getWorld()->damageOneActor(getWorld()->getOverlappingSocrates(this), 1);
	}
	else if (m_foodEaten == 3) {
		double newX = getX();
		double newY = getY(); 
		if (newX < VIEW_WIDTH / 2) {
			newX = newX + SPRITE_WIDTH; 
		}
		else if (newX > VIEW_WIDTH / 2) {
			newX = newX - SPRITE_WIDTH;
		}
		if (newY < VIEW_WIDTH / 2) {
			newY = newY + SPRITE_WIDTH;
		}
		else if (newY > VIEW_WIDTH / 2) {
			newY = newY - SPRITE_WIDTH;
		}
		getWorld()->addActor(new RegularSalmonella(newX, newY, getWorld()));
		m_foodEaten = 0;
	}
	else if (getWorld()->getOverlappingEdible(this) != nullptr) {
		m_foodEaten++;
		getWorld()->getOverlappingEdible(this)->setDead();
	}

	if (m_movementPlan > 0) {
		m_movementPlan--;
		double x, y;
		getPositionInThisDirection(getDirection(), 3, x, y);
		if ((!getWorld()->isBacteriumMovementBlockedAt(this, x, y)) && (getWorld()->distance(VIEW_WIDTH / 2.0, VIEW_HEIGHT / 2.0, x, y) <VIEW_RADIUS)) 
		{
			moveTo(x, y);
		}
		else {
			setDirection(randInt(0, 359));
			m_movementPlan = 10;
		}
	}
	else {
		int angle;
		if (getWorld()->getAngleToNearestNearbyEdible(this, 128, angle)) {

		}
		else {
			setDirection(randInt(0, 359));
			m_movementPlan = 10;
			return;
		}
	}


}

AggressiveSalmonella::AggressiveSalmonella(double startX, double startY, StudentWorld* world)
	:Salmonella(startX, startY, world, 10) {}

void AggressiveSalmonella::doSomething() {
	//
}