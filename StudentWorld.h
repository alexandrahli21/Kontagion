#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <vector>
#include <string>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

const double pi = 3.14159265;

class StudentWorld : public GameWorld
{
public: //add member functions but not member variables or data members
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    //int getNumActors();
   

private: //add data members, member functions
    vector<Actor*> m_actors;
    int m_totalActors;
    Socrates* m_socrates;
   
};

#endif // STUDENTWORLD_H_
