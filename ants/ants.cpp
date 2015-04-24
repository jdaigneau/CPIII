#include "ants.h"

World::World()
{
	// Initialize world to empty spaces
	int i,j;
	for (i=0; i<WORLDSIZE; i++)
	{
		for (j=0; j<WORLDSIZE; j++)
		{
			grid[i][j]=NULL;
		}
	}
}

World::~World()
{
	// Release any allocated memory
	int i,j;
	for (i=0; i<WORLDSIZE; i++)
	{
		for (j=0; j<WORLDSIZE; j++)
		{
			if (grid[i][j]!=NULL) delete (grid[i][j]);
		}
	}
}

// ======================
// getAt
// Returns the entry stored in the grid array at x,y
// ======================
Organism* World::getAt(int x, int y)
{
	if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
		return grid[x][y];
	return NULL;
}

void World::setAt(int x, int y, Organism *org)
{
	if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
	{
		grid[x][y] = org;
	}
}

// ======================
// Display
// Displays the world in ASCII.  Uses o for ant, X for doodlebug.
// ======================
void World::Display()
{
	int i,j;
	cout << endl << endl;
	for (j=0; j<WORLDSIZE; j++)
	{
		for (i=0; i<WORLDSIZE; i++)
		{
			if (grid[i][j]==NULL) 
				cout << ".";
			else if (grid[i][j]->getType()==ANT)
				cout << "o";
			else cout << "X";
		}
		cout << endl;
	}
}

// ======================
// SimulateOneStep
// This is the main routine that simulates one turn in the world.
// First, a flag for each organism is used to indicate if it has moved.
// This is because we iterate through the grid starting from the top
// looking for an organism to move . If one moves down, we don't want
// to move it again when we reach it.
// First move doodlebugs, then ants, and if they are still alive then
// we breed them.
// ======================
void World::SimulateOneStep()
{
	int i,j;
	// First reset all organisms to not moved
	for (i=0; i<WORLDSIZE; i++)
		for (j=0; j<WORLDSIZE; j++)
		{
			if (grid[i][j]!=NULL) grid[i][j]->moved = false;
		}
	// Loop through cells in order and move if it's a Doodlebug
	for (i=0; i<WORLDSIZE; i++)
		for (j=0; j<WORLDSIZE; j++)
		{
		 if ((grid[i][j]!=NULL) && (grid[i][j]->getType()==DOODLEBUG))
		 {
			if (grid[i][j]->moved == false) 
			{
			 grid[i][j]->moved = true; // Mark as moved
			 grid[i][j]->move();
			}
		 }
		}
	// Loop through cells in order and move if it's an Ant
	for (i=0; i<WORLDSIZE; i++)
		for (j=0; j<WORLDSIZE; j++)
		{
			if ((grid[i][j]!=NULL) && (grid[i][j]->getType()==ANT))
			{
				if (grid[i][j]->moved == false) 
				{
				 grid[i][j]->moved = true; // Mark as moved
				 grid[i][j]->move();
				}
			}
		}
	// Loop through cells in order and check if we should breed
	for (i=0; i<WORLDSIZE; i++)
		for (j=0; j<WORLDSIZE; j++)
		{
			// Kill off any doodlebugs that haven't eaten recently
			if ((grid[i][j]!=NULL) && 
			    (grid[i][j]->getType()==DOODLEBUG))
			{
				if (grid[i][j]->starve()) 
				{
					delete (grid[i][j]);
					grid[i][j] = NULL;
				}
			}
		}
	// Loop through cells in order and check if we should breed
	for (i=0; i<WORLDSIZE; i++)
		for (j=0; j<WORLDSIZE; j++)
		{
			// Only breed organisms that have moved, since
			// breeding places new organisms on the map we
			// don't want to try and breed those
			if ((grid[i][j]!=NULL) && (grid[i][j]->moved==true))
			{
				grid[i][j]->breed();
			}
		}
}

// ======================
// Organism Constructor
// Sets a reference back to the World object.
// ======================
Organism::Organism()
{
	world = NULL;	
	moved = false;
	breedTicks = 0;
	x=0; 
	y=0;
}
Organism::Organism(World *wrld, int x, int y)
{
	this->world = wrld;
	moved = false;
	breedTicks = 0;
	this->x=x; 
	this->y=y;
	wrld->setAt(x,y,this);
}

// ======================
// Organism destructor
// No need to delete the world reference,
// it will be destroyed elsewhere.
// ======================
Organism::~Organism()
{

}

// --------------------------------
// ----- ENTER YOUR CODE HERE -----
// --------------------------------

// Start with the Ant class


// ======================
// Ant constructor
// ======================
Ant::Ant() : Organism()
{
}

Ant::Ant(World *world, int x, int y) : Organism(world,x,y)
{
}

// ======================
// Ant Move
// Look for an empty cell up, right, left, or down and
// try to move there.
// ======================
void Ant::move()
{
	// Pick random direction to move
	int dir = rand() % 4;
	// Try to move up, if not at an edge and empty spot
	if (dir==0) 
	{
		if ((y>0) && (world->getAt(x,y-1)==NULL))
		{
		 world->setAt(x,y-1,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  
		 y--;
		}
	}
	// Try to move down
	else if (dir==1)
	{
		if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
		{
		 world->setAt(x,y+1,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  // Set current spot to empty
		 y++;
		}
	}
	// Try to move left
	else if (dir==2)
	{
		if ((x>0) && (world->getAt(x-1,y)==NULL))
		{
		 world->setAt(x-1,y,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  // Set current spot to empty
		 x--;
		}
	}
	// Try to move right
	else
	{
		if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
		{
		 world->setAt(x+1,y,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  // Set current spot to empty
		 x++;
		}
	}
}

// ======================
// Ant getType
// This virtual function is used so we can determine
// what type of organism we are dealing with.
// ======================
int Ant::getType()
{
	return ANT;
}

// ======================
// Ant breed
// Increment the tick count for breeding.
// If it equals our threshold, then clone this ant either
// above, right, left, or below the current one.
// ======================
void Ant::breed()
{
	breedTicks++;
	if (breedTicks == ANTBREED)
	{
		breedTicks = 0;
		// Try to make a new ant either above, left, right, or down
		if ((y>0) && (world->getAt(x,y-1)==NULL))
		{
			Ant *newAnt = new Ant(world, x, y-1);
		}
		else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
		{
			Ant *newAnt = new Ant(world, x, y+1);
		}
		else if ((x>0) && (world->getAt(x-1,y)==NULL))
		{
			Ant *newAnt = new Ant(world, x-1, y);
		}
		else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
		{
			Ant *newAnt = new Ant(world, x+1, y);
		}
	}
}

Doodlebug::Doodlebug() : Organism()
{
	starveTicks = 0;
}

Doodlebug::Doodlebug(World *world, int x, int y) : Organism(world,x,y)
{
	starveTicks = 0;
}

void Doodlebug::move()
{
	// Look in each direction and if a bug is found move there
	// and eat it.
	if ((y>0) && (world->getAt(x,y-1)!=NULL) &&
		     (world->getAt(x,y-1)->getType() == ANT))
	{
		delete (world->grid[x][y-1]);  // Kill ant
		world->grid[x][y-1] = this;    // Move to spot
		world->setAt(x,y,NULL);  
		starveTicks =0 ;	  	// Reset hunger
		y--;
		return;
	}
	else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)!=NULL) &&
		     (world->getAt(x,y+1)->getType() == ANT))
	{
		delete (world->grid[x][y+1]);  // Kill ant
		world->grid[x][y+1] = this;    // Move to spot
		world->setAt(x,y,NULL);  
		starveTicks =0 ;	  	// Reset hunger
		y++;
		return;
	}
	else if ((x>0) && (world->getAt(x-1,y)!=NULL) &&
		     (world->getAt(x-1,y)->getType() == ANT))
	{
		delete (world->grid[x-1][y]);  // Kill ant
		world->grid[x-1][y] = this;    // Move to spot
		world->setAt(x,y,NULL);  
		starveTicks =0 ;	  	// Reset hunger
		x--;
		return;
	}
	else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)!=NULL) &&
		     (world->getAt(x+1,y)->getType() == ANT))
	{
		delete (world->grid[x+1][y]);  // Kill ant
		world->grid[x+1][y] = this;    // Move to spot
		world->setAt(x,y,NULL);  
		starveTicks =0 ;	  	// Reset hunger
		x++;
		return;
	}

	
	// If we got here, then we didn't find food.  Move
	// to a random spot if we can find one.
	int dir = rand() % 4;
	// Try to move up, if not at an edge and empty spot
	if (dir==0) 
	{
		if ((y>0) && (world->getAt(x,y-1)==NULL))
		{
		 world->setAt(x,y-1,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  
		 y--;
		}
	}
	// Try to move down
	else if (dir==1)
	{
		if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
		{
		 world->setAt(x,y+1,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  // Set current spot to empty
		 y++;
		}
	}
	// Try to move left
	else if (dir==2)
	{
		if ((x>0) && (world->getAt(x-1,y)==NULL))
		{
		 world->setAt(x-1,y,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  // Set current spot to empty
		 x--;
		}
	}
	// Try to move right
	else
	{
		if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
		{
		 world->setAt(x+1,y,world->getAt(x,y));  // Move to new spot
		 world->setAt(x,y,NULL);  // Set current spot to empty
		 x++;
		}
	}
	starveTicks++;		// Increment starve tick since we didn't
				// eat on this turn
}

// ======================
// Doodlebug getType
// This virtual function is used so we can determine
// what type of organism we are dealing with.
// ======================
int Doodlebug::getType()
{
	return DOODLEBUG;
}

// ======================
// Doodlebug breed
// Creates a new doodlebug adjacent to the current cell
// if the breedTicks meets the threshold.
// ======================
void Doodlebug::breed()
{
	breedTicks++;
	if (breedTicks == DOODLEBREED)
	{
		breedTicks = 0;
		// Try to make a new ant either above, left, right, or down
		if ((y>0) && (world->getAt(x,y-1)==NULL))
		{
			Doodlebug *newDoodle = new Doodlebug(world, x, y-1);
		}
		else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
		{
			Doodlebug *newDoodle = new Doodlebug(world, x, y+1);
		}
		else if ((x>0) && (world->getAt(x-1,y)==NULL))
		{
			Doodlebug *newDoodle = new Doodlebug(world, x-1, y);
		}
		else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
		{
			Doodlebug *newDoodle = new Doodlebug(world, x+1, y);
		}
	}
}

// ======================
// Doodlebug starve
// Returns true or false if a doodlebug should die off
// because it hasn't eaten enough food.
// ======================
bool Doodlebug::starve()
{
	// Starve if no food eaten in last DOODLESTARVE time ticks
	if (starveTicks > DOODLESTARVE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// --------------------------------
// --------- END USER CODE --------
// --------------------------------

