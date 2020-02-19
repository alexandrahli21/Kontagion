#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}
//
//int StudentWorld::getNumActors() {
//   // return m_totalActors;
//}


int StudentWorld::init()
{
    
   // int numActors = getNumActors();
    Socrates* socratesPtr = new Socrates(); //pointer to newly created socrates object
    
    double pi = 3.14159265;
    for (int i = 0; i < max(180 - 20 * getLevel(), 20); i++) {
        int x = randInt(0, 360);
        double deg = (x * 2 * pi)/360;
        int y = randInt(0, 120);
        Dirt * dirtPtr = new Dirt(y*cos(deg)+128, y*sin(deg)+128);
    }
    
   

     //vector<Actor*> actors(numActors); //keep track of all actors except Socrates
    //initialize data structures used to keep track of game's world
    //allocate and insert a socrates object into game world 
    //allocate and insert various piles of dirt, pits, and food objects into game world 
    //initialize remaining bacteria that needs to be destroyed on this level before socrates can advance to next level
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
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
