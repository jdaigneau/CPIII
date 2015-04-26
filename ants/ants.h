/* 
 * File:   ants.h
 * Author: jeremydaigneau
 *
 * Created on April 23, 2015, 7:57 PM
 */

#ifndef ANTS_H
#define	ANTS_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

const int WORLDSIZE = 20;
const int INITIALANTS = 100;
const int INITIALBUGS = 5;
const int DOODLEBUG = 1;
const int ANT = 2;
const int ANTBREED = 3;
const int DOODLEBREED = 8;
const int DOODLESTARVE = 3;

class Organism;
class Doodlebug;
class Ant;

class World
{
    friend class Organism;			
    friend class Doodlebug;			
    friend class Ant;			

public:
    World();
    ~World();
    Organism* getAt(int x, int y);
    void setAt(int x, int y, Organism *org);
    void Display();
    void SimulateOneStep();

private:
	Organism* grid[WORLDSIZE][WORLDSIZE];
};

class Organism
{
friend class World;			
public:
	Organism();
	Organism(World *world, int x, int y);
	~Organism();
	virtual void breed() = 0;	
	virtual void move() = 0;	
	virtual int getType() =0;	
	virtual bool starve() = 0;
	
protected:
	int x,y;			
	bool moved;			
	int breedTicks;			
	World *world;
};

class Ant : public Organism
{
 friend class World;
 public:
	Ant();
	Ant(World *world, int x, int y);
	virtual void breed();	
	virtual void move();	
	virtual int getType();	
	virtual bool starve()   
	  { return false; }
};

class Doodlebug : public Organism
{
 friend class World;
 public:
	Doodlebug();
	Doodlebug(World *world, int x, int y);
	virtual void breed();	
	virtual void move();	
	virtual int getType();	
	virtual bool starve();
	
 private:
	int starveTicks;	
};

#endif	/* ANTS_H */

