#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world, bool damageable)
	: GraphObject(imageID, startX, startY, dir, depth, size), m_world(world), m_damageable(damageable), m_dead(false), m_type(imageID) {}

StudentWorld* Actor::getWorld() const
{
	return m_world;
}

int Actor::getType() const {
	return m_type;
}

Agent::Agent(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world, bool damageable)
	:Actor(imageID, startX, startY, dir, depth, size, world, damageable) {}

void Agent::doSomething(){}

Socrates::Socrates(StudentWorld* world)
	:Agent(IID_PLAYER, 0, (VIEW_HEIGHT / 2), 0, 0, 1.0, world, true) {}

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
	//lets user pick a direction by hitting a directional key
	//adjust socrate's coordinates around the the perimeter of the petri dish
	//set direction that socrates is facing to his positional angle+180
	//moveTo(double x, double y);
}

Pit::Pit(double startX, double startY, StudentWorld* world)
	:Actor(IID_PIT, startX, startY, 0, 1, 1.0, world, false) {}

void Pit::doSomething() 
{
}

Dirt::Dirt(double startX, double startY, StudentWorld* world)
	:Actor(IID_DIRT, startX, startY, 0, 1, 1.0, world, true) {}

void Dirt::doSomething() //do nothing every tick
{}
