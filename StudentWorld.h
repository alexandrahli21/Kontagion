#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <list>
#include <string>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

const double pi = 3.14159265;

class StudentWorld : public GameWorld
{
public: //add member functions but not member variables or data members
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    double distance(double x1, double y1, double x2, double y2);
    bool overlap(int imageID, double randX, double randY);
    void addActor(Actor* actor);
    void deleteEndActor();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    //int getNumActors();
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
