#include "StudentWorld.h"

#include <string>
#include <cmath>
#include <math.h>
using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_totalActors(0)
{}

StudentWorld::~StudentWorld() {
    cleanUp();
}


double StudentWorld::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

//return true if overlaps with another actor
bool StudentWorld::overlap(int imageID, double randX, double randY)
{
    list<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if ((*it)->getType() == imageID)
        {
            if (distance((*it)->getX(), (*it)->getY(), randX, randY) < SPRITE_WIDTH) {
                return true;
            }
        }
        it++;
    }
    return false;
}

void StudentWorld::addActor(Actor* actor)
{
    m_actors.push_back(actor);
    m_totalActors++;
}

void StudentWorld::deleteEndActor() 
{
    list<Actor*>::iterator it;
    it = m_actors.end();
    it--;
    delete* it;
    m_actors.erase(it);
    m_totalActors--;
}

int StudentWorld::init()
{
    //allocate and insert a socrates object into game world 
    m_socrates = new Socrates(this); //pointer to newly created socrates object
   // vector<Actor*> m_actors(m_totalActors); //keep track of all actors except Socrates

   
    //allocate and insert dirt into game world
    
    for (int i = 0; i < max(180 - 20 * getLevel(), 20); i++) {
        double deg = (randInt(0, 360) * 2 * pi) / 360;
        double rad = (12) * sqrt(randInt(0, 100));
        addActor(new Dirt((rad * cos(deg) + 128), (rad * sin(deg) + 128), this));
       /*
        if (overlap(IID_DIRT, rad * cos(deg) + 128, rad * sin(deg) + 128)) {
            deleteEndActor();
            i--;
        }
        */
    }
 
    
    //allocate and insert pit(s) into game world
    for (int i = 0; i < getLevel(); i++) {
        double deg = ((2 * randInt(0, 360) * pi) / 360);
        double rad = (12) * sqrt(randInt(0, 100));

        addActor(new Pit(rad * cos(deg) + 128, rad * sin(deg) + 128, this));
    }
    
    //in a manner such that no two pits
   // overlap with each other(their centers must be more than SPRITE_WIDTH
      //  pixels apart from each other).

    
   //initialize data structures used to keep track of game's world

   //allocate and insert various piles of dirt, pits, and food objects into game world 
   //initialize remaining bacteria that needs to be destroyed on this level before socrates can advance to next level
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_socrates->doSomething();

    //for each actor, do something 
    list<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        (*it)->doSomething();
        it++;
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
    list<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        delete* it;
        m_actors.erase(it);
        it = m_actors.begin(); //revalidate pointer
    }
    if (m_socrates != nullptr) {
        delete m_socrates;
        m_socrates = nullptr;
    }
    m_totalActors = 0;
}



/*
GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_totalActors(0)
{}

StudentWorld::~StudentWorld() {
    cleanUp();
}

void StudentWorld::addActor(Actor* actor)
{
    m_actors.push_back(actor);
    m_totalActors++;
}

double StudentWorld::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
}

//return true if overlaps with another actor
bool StudentWorld::overlap(int imageID, double randX, double randY)
{
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if ((*it)->getType() == imageID )
        {
            if (distance((*it)->getX(), (*it)->getY(), randX, randY) < SPRITE_WIDTH) {
                return true;
            }
        }
        it++;
    }
    return false;
}

int StudentWorld::init()
{
    //allocate and insert a socrates object into game world 
    m_socrates = new Socrates(this); //pointer to newly created socrates object

     //allocate and insert dirt into game world
    for (int i = 0; i < max(180 - 20 * getLevel(), 20); i++) {
        double deg = ((2 * randInt(0, 360) * pi) / 360);
        double rad = (12) * sqrt(randInt(0, 100));
        addActor(new Dirt(rad * cos(deg) + 128, rad * sin(deg) + 128, this));
       
    }

    //allocate and insert pit(s) into game world
    for (int i = 0; i < getLevel(); i++) {
        double deg = ((2 * randInt(0, 360) * pi) / 360);
        double rad = (12) * sqrt(randInt(0, 100));
       
        addActor(new Pit(rad * cos(deg) + 128, rad * sin(deg) + 128, this));
    }
    //in a manner such that no two pits
   // overlap with each other(their centers must be more than SPRITE_WIDTH
      //  pixels apart from each other).

   


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
    vector<Actor*>::iterator it; 
    it = m_actors.begin();
    while (it != m_actors.end()) {
        (*it)->doSomething();
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
    vector<Actor*>::iterator it; 
    it = m_actors.begin();
    while (it != m_actors.end()) {
        delete* it; 
        m_actors.erase(it);
        it = m_actors.begin(); //revalidate pointer
    }
    if (m_socrates != nullptr) {
        delete m_socrates;
        m_socrates = nullptr;
    }
    m_totalActors = 0;
}

*/