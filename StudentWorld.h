#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <list>
#include <algorithm>
#include <string>

class Actor;
class Soctates;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

const double pi = 3.14159265;

class StudentWorld : public GameWorld
{
public: //add member functions but not member variables or data members
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();

    virtual int init();
    virtual int move();
    virtual void cleanUp();

    double distance(double x1, double y1, double x2, double y2) const;
    void generateNonoverlapCoord(double &newX, double &newY);
    bool initOverlap(double randX, double randY);
    void addActor(Actor* actor);
    bool damageOneActor(Actor* a, int damage);
    bool isBacteriumMovementBlockedAt(Actor* a, double x, double y) const ;
    Socrates* getOverlappingSocrates(Actor* a) const;
    Actor* getOverlappingEdible(Actor* a) const;
    bool getAngleToNearbySocrates(Actor* a, int dist, int& angle) const;
    bool getAngleToNearestNearbyEdible(Actor* a, int dist, int& angle) const;
    void getPositionOnCircumference(int angle, double& x, double& y) const;
private: //add data members, member functions
    std::list<Actor*> m_actors;
    int m_totalActors;
    Socrates* m_socrates;

};

#endif // STUDENTWORLD_H_
/*




class StudentWorld : public GameWorld
{
public: //add member functions but not member variables or data members
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    double distance(double x1, double y1, double x2, double y2);
    bool overlap(int imageID, double randX, double randY);
    void addActor(Actor* actor);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    //int getNumActors();
   

private: //add data members, member functions
    std::vector<Actor*> m_actors;
    int m_totalActors;
    Socrates* m_socrates;
   
};

#endif // STUDENTWORLD_H_
*/
