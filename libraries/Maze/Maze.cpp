#include <Maze.h>

Maze::Maze() {
	facing = N;
	maze = new Node[2*SIZE];
	for(int i = 0; i < 2*SIZE; i++) {
		maze[i].wall = NULL;
		maze[i].prev = NULL;
	}
	current = &maze[SIZE];
}

Maze::~Maze() {
	free(maze);
	free(current);
}

int8_t Maze::getNext(uint8_t sensor) {
	Node* next;
	uint8_t nextDir;
	current->wall = rshift(sensor,offset());
	uint8_t wall = sensor;
        Serial.print("logical wall is: ");
        Serial.println(wall);
	if(!(wall & 8) && (current+northofcurrent())->wall == NULL) {
		Serial.println("moving to north");
		next = current + northofcurrent();
		next->prev = current;
		nextDir = N;
		finalseq.push(N);
	}
	else if(!(wall & 4) && (current+eastofcurrent())->wall == NULL) {
		Serial.println("moving to east");
		next = current + eastofcurrent();
		next->prev = current;
		facing = rshift(facing,1);
		nextDir = E;
		finalseq.push(E);
	}
	else if(!(wall & 1) && (current+westofcurrent())->wall == NULL) {
		Serial.println("moving to west");
		next = current + westofcurrent();
		next->prev = current;
		facing = rshift(facing,3);
		nextDir = W;
		finalseq.push(W);
	}
	else if(!(wall & 2) && (current+westofcurrent())->wall == NULL) {
		Serial.println("moving to south");
		next = current + southofcurrent();
		next->prev = current;
		facing = rshift(facing,2);
		nextDir = S;
		finalseq.push(S);
	}
	else {
		Serial.println("going back to prev");
		next->prev = current;
		facing = rshift(facing,2);
		nextDir = S;
		finalseq.pop();
	}
	nextIndex = next - current;
	current = next;
	return nextDir;
}

QueueArray<uint8_t> Maze::getPath() {
	return finalseq;
}

uint8_t Maze::offset() {
	switch(facing) {
	  case N: return 0; break;
	  case E: return 1; break;
	  case S: return 2; break;
	  case W: return 3; break;
	}
}

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

uint8_t lshift(uint8_t x, uint8_t i) {
	return (x << i) & 15 | (x >> (4-i));
}

uint8_t rshift(uint8_t x, uint8_t i) {
	return (x << (4-i)) & 15 | (x >> i);
}

