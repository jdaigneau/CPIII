#include "ants.h"

World::World()
{
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
	int i,j;
	for (i=0; i<WORLDSIZE; i++)
	{
		for (j=0; j<WORLDSIZE; j++)
		{
			if (grid[i][j]!=NULL) delete (grid[i][j]);
		}
	}
}

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

void World::SimulateOneStep()
{
	int i,j;
	
	for (i=0; i<WORLDSIZE; i++)
		for (j=0; j<WORLDSIZE; j++)
		{
			if (grid[i][j]!=NULL) grid[i][j]->moved = false;
		}
	
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

Organism::~Organism()
{

}

Ant::Ant() : Organism()
{
}

Ant::Ant(World *world, int x, int y) : Organism(world,x,y)
{
}

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

int Ant::getType()
{
	return ANT;
}

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

int Doodlebug::getType()
{
	return DOODLEBUG;
}

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


