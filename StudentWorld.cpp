#include "StudentWorld.h"

#include <string>
#include <cmath>

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_totalActors(0)
{}
//
//int StudentWorld::getNumActors() {
//   // return m_totalActors;
//}
StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init()
{
    //allocate and insert a socrates object into game world 
    m_socrates = new Socrates(this); //pointer to newly created socrates object

    //allocate and insert dirt into game world
    for (int i = 0; i < max(180 - 20 * getLevel(), 20); i++) {
        double deg = (randInt(0, 360) * 2 * pi)/360;
        double rad = (12)* sqrt(randInt(0, 100));
        Dirt * dirtPtr = new Dirt(rad*cos(deg)+128, rad*sin(deg)+128, this);
        m_totalActors++;
    }

     vector<Actor*> m_actors(m_totalActors); //keep track of all actors except Socrates
    //initialize data structures used to keep track of game's world

    //allocate and insert various piles of dirt, pits, and food objects into game world 
    //initialize remaining bacteria that needs to be destroyed on this level before socrates can advance to next level
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_socrates->doSomething();

    //for each actor, do something 
    for (int i = 0; i < m_totalActors; i++) {
       
    }
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_CONTINUE_GAME;
   // return GWSTATUS_PLAYER_WON;
   // return GWSTATUS_FINISHED_LEVEL;
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    //delete* socrates;
}
