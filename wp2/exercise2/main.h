// File: main.h

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 2
// Exercise 2
// Submission code: 450999

#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 100

// Enums
typedef enum { NORTH, EAST, SOUTH, WEST } Directions;

typedef struct {
  // xPos and yPos are coordinate representations
  // isAlive is a flag to track the robot being
  // within bounds or not
  int xPos, yPos, isAlive;
  Directions directions;
} Robot;

// Function declarations
void move(Robot *robot);
void turn(Robot *robot);
void readInitialCoords(Robot *robot);
void readInstructionsInput(char *);
int validateCoordInput(const int inputOk, const int coord);
int validateInstructionsInput(char *);
void drawGrid(const Robot *robot);
void drawRobot(const int robotDirection);
void clearInputBuffer(void);
void peekInputBuffer(void);
