#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <vector>
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public: //add member functions but not member variables or data members
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    //int getNumActors();
    ~StudentWorld()
    {
      // cleanUp();
    }

private: //add data members, member functions
  /*  int m_level, m_lives, m_totalActors;*/
   
};

#endif // STUDENTWORLD_H_
