#ifndef __MAZE_H__
#define __MAZE_H__

#include <Arduino.h>
#include <QueueArray.h>

#define ROW 3
#define COL 3
#define SIZE ROW*COL

enum cardinal {
	N=8,
	E=4,
	S=2,
	W=1
};

class Node {
public:
	uint8_t wall;
	Node* prev;
};

class Maze {
	
public:	
	int nextIndex;
	Maze();
	~Maze();
	int8_t getNext(uint8_t);
	QueueArray<uint8_t> getPath();
	
private:
	QueueArray<uint8_t> finalseq;
	uint8_t facing;
	Node* current;
	Node* maze;
	uint8_t offset();
	int8_t northofcurrent();
	int8_t eastofcurrent();
	int8_t southofcurrent();
	int8_t westofcurrent();
	
};

uint8_t lshift(uint8_t, uint8_t);
uint8_t rshift(uint8_t, uint8_t);

#endif
