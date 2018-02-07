#ifndef __MAZE_H__
#define __MAZE_H__

#include <Arduino.h>
#include <QueueArray.h>
#include <StackArray.h>

/* Maze dimension configuration */
#define ROW 10
#define COL 10
#define SIZE ROW*COL

/* cardinal direction encodings */
enum cardinal {
	N=8,
	E=4,
	S=2,
	W=1
};

/* object class for a cell in the maze.
 * maze is composed of objects of nodes
 */
class Node {
public:
	uint8_t wall;
	Node* prev;
};

class Maze {
	
public:	
	Maze();
	~Maze();
	//returns next direction to move to
	int8_t getNext(uint8_t);
	//returns sequence of directions from start to goal
	QueueArray<uint8_t> getPath();	
private:
	QueueArray<uint8_t> finalseq;
        StackArray<uint8_t> dirlist;
	uint8_t facing;
	uint8_t mutex = 1;
        Node* current;
	Node* maze;
	
	//function to find how much offset between reference and relative direction
	uint8_t offset();
	
	//helper functions to offset reference direction with relative direction
	int8_t northofcurrent();
	int8_t eastofcurrent();
	int8_t southofcurrent();
	int8_t westofcurrent();
	
};

//cyclical 4-bit shift functions 
uint8_t lshift(uint8_t, uint8_t);
uint8_t rshift(uint8_t, uint8_t);

#endif
