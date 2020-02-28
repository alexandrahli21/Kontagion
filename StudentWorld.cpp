#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <cmath>
#include <math.h>
#include <iostream>
using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_totalActors(0) {}

StudentWorld::~StudentWorld() {
    cleanUp();
}


double StudentWorld::distance(double x1, double y1, double x2, double y2) const
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


void StudentWorld::generateNonoverlapCoord(double &newX, double &newY)
{
    bool contLoop = true;
    while (contLoop) {
        double deg = (randInt(0, 360) * 2.0 * pi) / 360.0;
        double rad = (12.0) * sqrt(randInt(0, 100));
        newX = (rad * cos(deg) + 128.0);
        newY = (rad * sin(deg) + 128.0);
        list<Actor*>::iterator it;
        it = m_actors.begin();

        bool finished = true; 
        while (it != m_actors.end()) {
            double xCoord = (*it)->getX();
            double yCoord = (*it)->getY();
            if (distance(xCoord, yCoord, newX, newY) <= SPRITE_WIDTH) {
                finished = false;
                break;
            }
            it++;
        }
        if (finished) {
            contLoop = false;
        }
    }
}


void StudentWorld::addActor(Actor* actor)
{
    m_actors.push_back(actor);
    m_totalActors++;
}


// If actor a ovelaps some live actor, damage that live actor by the
    // indicated amount of damage and return true; otherwise, return false.
bool StudentWorld::damageOneActor(Actor* a, int damage) 
{
    double x = a->getX();
    double y = a->getY();
    list<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if (!(*it)->isDead()) //live actor
        {
            if (distance(x, y, (*it)->getX(), (*it)->getY()) <= (SPRITE_WIDTH)) {
                (*it)->takeDamage(damage);
                return true;
            }
        }
        it++;
    }
    return false;
}

// Is bacterium a blocked from moving to the indicated location?
bool StudentWorld::isBacteriumMovementBlockedAt(Actor* a, double x, double y) const {
    list<Actor*>::const_iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if ((*it)->blocksBacteriumMovement()) {
            if (distance((*it)->getX(), (*it)->getY(), x, y) <= (SPRITE_WIDTH / 2)) {
                return true;
            }
        }
        it++;
    }
    return false;
}


// If actor a overlaps this world's socrates, return a pointer to the
// socrates; otherwise, return nullptr
Socrates* StudentWorld::getOverlappingSocrates(Actor* a) const {
    double x = a->getX();
    double y = a->getY();
    double socX = m_socrates->getX();
    double socY = m_socrates->getY();
    if (distance(x, y, socX, socY) <= SPRITE_WIDTH) {
        return m_socrates;
    }
    else
        return nullptr;
}

// If actor a overlaps a living edible object, return a pointer to the
   // edible object; otherwise, return nullptr
Actor* StudentWorld::getOverlappingEdible(Actor* a) const 
{
    double x = a->getX();
    double y = a->getY();
    list<Actor*>::const_iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if (!(*it)->isDead() && (*it)->isEdible()) //live actor
        {
            if (distance(x, y, (*it)->getX(), (*it)->getY()) <= (SPRITE_WIDTH)) {
                return *it;
            }
        }
        it++;
    }
    return nullptr;
}


// Return true if this world's socrates is within the indicated distance
    // of actor a; otherwise false.  If true, angle will be set to the
    // direction from actor a to the socrates.
bool StudentWorld::getAngleToNearbySocrates(Actor* a, int dist, int& angle) const {
    double x = a->getX();
    double y = a->getY();
    double socX = m_socrates->getX();
    double socY = m_socrates->getY();
    if (distance(x, y, socX, socY) <= dist) {
        angle = atan2((socY - y), (socX - x));
        return true;
    }
    else
        return false;
}


// Return true if there is a living edible object within the indicated
    // distance from actor a; otherwise false.  If true, angle will be set
    // to the direction from actor a to the edible object nearest to it.
bool StudentWorld::getAngleToNearestNearbyEdible(Actor* a, int dist, int& angle) const 
{
    Actor* ptrClosest = nullptr;
    bool edible = false;
    double minDistance = 0;
    double x = a->getX();
    double y = a->getY();
    list<Actor*>::const_iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if (!(*it)->isDead() && (*it)->isEdible()) //live actor
        {
            double dis = distance(x, y, (*it)->getX(), (*it)->getY());
            if (dis <= dist) {
                if (ptrClosest = nullptr){
                    ptrClosest = (*it);
                    minDistance = dis;
                    edible = true;
                }
                else {
                    if (dis < minDistance) {
                        minDistance = dis;
                        ptrClosest = (*it);
                    }
                }
            }
        }
        it++;
    }
    if (edible) {
        angle = atan2((*it)->getY() - y, ((*it)->getX() - x));
    }
    return edible;

}

// Set x and y to the position on the circumference of the Petri dish
    // at the indicated angle from the center.  (The circumference is
    // where socrates and goodies are placed.)
void StudentWorld::getPositionOnCircumference(int angle, double& x, double& y) const {
    x = 120.0 * sin(angle) + 128.0;
    y = 120.0 * cos(angle) + 128.0;
}

int StudentWorld::init()
{
   
    //allocate and insert a socrates object into game world 
    m_socrates = new Socrates(0, (VIEW_HEIGHT / 2), this); //pointer to newly created socrates object
   // vector<Actor*> m_actors(m_totalActors); //keep track of all actors except Socrates

    //allocate and insert dirt into game world
    for (int i = 0; i < max(180 - 20 * getLevel(), 20); i++) {
        double deg = (randInt(0, 360) * 2.0 * pi) / 360.0;
        double rad = (12.0) * sqrt(randInt(0, 100));
        addActor(new Dirt((rad * cos(deg) + 128.0), (rad * sin(deg) + 128.0), this));
    }

    //allocate and insert pit(s) into game world
    for (int i = 0; i < getLevel(); i++) {
        double x, y;
        generateNonoverlapCoord(x, y);
        addActor(new Pit(x, y, this)); 
    }

    //allocate and insert food into game world
    for (int i = 0; i < min(5 * getLevel(), 25); i++) {
       double q, r;
       generateNonoverlapCoord(q, r);
       addActor(new Food(q, r, this));
    }
    
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