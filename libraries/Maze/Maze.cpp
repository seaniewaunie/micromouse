#include <Maze.h>

/* Maze initialization */
Maze::Maze() {
	/* Entry point is set to North reference direction */ 
	facing = N;
	
	maze = new Node[2*SIZE];
	for(int i = 0; i < 2*SIZE; i++) {
		maze[i].wall = NULL;
		maze[i].prev = NULL;
	}
	current = &maze[SIZE];
}

/* Maze destruction */
Maze::~Maze() {
	free(maze);
	free(current);
}

/* method returns next cardinal direction to move to
 * in reference to current facing directions.
 * ex. if mouse is facing east, W retured by the function 
 * is actually North in the reference direction. After execution 
 * mouse is facing North again.
 */
int8_t Maze::getNext(uint8_t sensor){
    // unfortunately the previous algorithm just won't work, there's too many exception cases
}


/*
int8_t Maze::getNext(uint8_t sensor) {
	Node* next;
	uint8_t nextDir;
	uint8_t wall;
	int nextIndex;
	
	// if this cell hasnt been visited 
        
	if(current->wall == NULL) {
		//store wall configuration in memory in the reference direction viewpoint
		current->wall = rshift(sensor,offset());
		//use relative direction viewpoint for further calculation
		wall = sensor;
	}
	// if this cell has been visited before, use wall configuration from the memory 
	else {
		// wall configuration in memory is in reference direction, shift it to the current relative direction 
                 
		wall = lshift(current->wall,offset());
                Serial.println("I've been here before, I'm using my memory!");

	}
	
	// find next cell to move to cell must not have wall between and cell must be unvisited
	if(!(wall & 8)) {
            Serial.println("I know north is open");
            if((current + northofcurrent())->wall == NULL){
		Serial.println("moving to unexplored north");
                // next memory address to jump to
		next = current + northofcurrent();
		// set current cell as the cell traveled from 
		next->prev = current;
		// next direction to move to
		nextDir = N;
                // since moving straight, no need to adjust facing directions
		
		// add this movement to stack
		finalseq.push(N);
                dirlist.push(N);
            }
            else{
                Serial.println("I'm going to check the other directions before going there");
                if(!(wall & 4)) {
                    Serial.println("moving to east");
                    next = current + eastofcurrent();
                    next->prev = current;
                    //adjust facing direction
                    facing = rshift(facing,1);
                    nextDir = E;
                    finalseq.push(E);
                    dirlist.push(E);
                }
                else if(!(wall & 1)) {
                    Serial.println("moving to west");
                    next = current + westofcurrent();
                    next->prev = current;
                    facing = rshift(facing,3);
                    nextDir = W;
                    finalseq.push(W);
                    dirlist.push(W);
                }
                else{
                    Serial.println("moving to explored north");
                    // next memory address to jump to
                    next = current + northofcurrent();
                    // set current cell as the cell traveled from
                    next->prev = current;
                    // next direction to move to
                    nextDir = N;
                    // since moving straight, no need to adjust facing directions
                    
                    // add this movement to stack
                    finalseq.push(N);
                    dirlist.push(N);
                }

            }
	}
	else if(!(wall & 4)) {
            Serial.println("I know east is open");
            if((current + eastofcurrent())->wall == NULL){
		Serial.println("moving to unexplored east");
		next = current + eastofcurrent();
		next->prev = current;
		//adjust facing direction
		facing = rshift(facing,1);
		nextDir = E;
		finalseq.push(E);
                dirlist.push(E);
            }
            else{
                Serial.println("I'm going to check west before making my decision");
                // if west is open and not the start of the maze
                if(!(wall & 1) && mutex == 0) {
                    Serial.println("moving west to starting point");
                    next = current + westofcurrent();
                    next->prev = current;
                    facing = rshift(facing,3);
                    nextDir = W;
                    finalseq.push(W);
                    dirlist.push(W);
                
                }
                else{
                    Serial.println("Moving to explored east");
                    next = current + eastofcurrent();
                    next->prev = current;
                    //adjust facing direction
                    facing = rshift(facing,1);
                    nextDir = E;
                    finalseq.push(E);
                    dirlist.push(E);
                    
                    // in order to avoid infinite right turning loops, check east one more time
                    mutex = 0;
                }
            }
	}
	else if(!(wall & 1)) {
            if((current+westofcurrent())->wall == NULL){
		Serial.println("moving to unexplored west");
		next = current + westofcurrent();
		next->prev = current;
		facing = rshift(facing,3);
		nextDir = W;
		finalseq.push(W);
                dirlist.push(W);
            }
            else{
                Serial.println("all surrounding nodes have been explored before... I need to backtrack");
                
                if(!(wall & 8)){
                    Serial.println("moving to explored north");
                    // next memory address to jump to 
                    next = current + northofcurrent();
                    // set current cell as the cell traveled from
                    next->prev = current;
                    // next direction to move to
                    nextDir = N;
                    // since moving straight, no need to adjust facing directions
                    
                    // add this movement to stack
                    finalseq.push(N);
                    dirlist.push(N);
                }
                else if(!(wall & 4)){
                    Serial.println("Moving to explored east");
                    next = current + eastofcurrent();
                    next->prev = current;
                    //adjust facing direction
                    facing = rshift(facing,1);
                    nextDir = E;
                    finalseq.push(E);
                    dirlist.push(E);
                }
                else{
                    Serial.println("moving to explored west");
                    next = current + westofcurrent();
                    next->prev = current;
                    facing = rshift(facing,3);
                    nextDir = W;
                    finalseq.push(W);
                    dirlist.push(W);

                }


            }
	}
	else if(!(wall & 2)) {
                // the only time we ever move south is in a dead end.
                Serial.println("moving to south");
                next = current + southofcurrent();
		next->prev = current;
		//Serial.println("gets here 1");

                facing = rshift(facing,2);
                //Serial.println("gets here 2");

		nextDir = S;
		//Serial.println("gets here 3");

                finalseq.push(S);
                //Serial.println("gets here 4");

                dirlist.push(S);
                //Serial.println("gets here 5");
                
	}
        
        /* Sean commented this out because it is un-needed. Our final sequence should be parsed
         * to find "backtracking" and remove it.. or edit it, and this will give us our "shortest path"
         * for now we have a "path"
	else {
        // TODO: This causes the program to crash when entering a dead end
		Serial.println("going back to prev");
		next = current->prev;
                //facing = rshift(facing, 2);
                Serial.print(dirlist.peek());
                nextDir = rshift(dirlist.pop(),2);
                facing = nextDir;
		finalseq.pop();
	}
        //
	current = next;
	return nextDir;
}
*/
QueueArray<uint8_t> Maze::getPath() {
	return finalseq;
}

/* function to find out how many circular shift is needed to 
 * adjust reference direction and relative direction
 * 
 * ex. facing south, Front wall is 8 but it is actually 2 from the reference point
 * therefore, it needs to 2 circular shift to the right.
 */
uint8_t Maze::offset() {
	switch(facing) {
	  case N: return 0; break;
	  case E: return 1; break;
	  case S: return 2; break;
	  case W: return 3; break;
	}
}

/* find out next memory address to jump to relative to current facing direction
 * 
 * THESE FUNCTIONS WILL BE REPLACED WITH BETTER LOGIC!!!
 */
int8_t Maze::northofcurrent() {
  switch(facing) {
  case N: return -ROW; break;
  case E: return 1; break;
  case S: return ROW; break;
  case W: return -1; break;
  }
}

int8_t Maze::eastofcurrent() {
  switch(facing) {
  case N: return 1; break;
  case E: return ROW; break;
  case S: return -1; break;
  case W: return -ROW; break;
  }
}

int8_t Maze::southofcurrent() {
  switch(facing) {
  case N: return ROW; break;
  case E: return -1; break;
  case S: return -ROW; break;
  case W: return 1; break;
  }
}

int8_t Maze::westofcurrent() {
  switch(facing) {
  case N: return -1; break;
  case E: return -ROW; break;
  case S: return 1; break;
  case W: return ROW; break;
  }
}

/* 4-bit circular shift */
uint8_t lshift(uint8_t x, uint8_t i) {
	return (x << i) & 15 | (x >> (4-i));
}

uint8_t rshift(uint8_t x, uint8_t i) {
	return (x << (4-i)) & 15 | (x >> i);
}

