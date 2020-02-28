#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <list>
#include <string>


const double pi = 3.14159265;

class StudentWorld : public GameWorld
{
public: //add member functions but not member variables or data members
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    double distance(double x1, double y1, double x2, double y2);
    void generateNonoverlapCoord(double &newX, double &newY);
    void addActor(Actor* actor);
   
    virtual int init();
    virtual int move();
    virtual void cleanUp();
private: //add data members, member functions
    std::list<Actor*> m_actors;
    int m_totalActors;
    Socrates* m_socrates;
};

#endif  //STUDENTWORLD_H_
