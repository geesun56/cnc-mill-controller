#ifndef OPERATION_H_
#define OPERATION_H_

#define CM 10
#define MM 1
 
#define MAX_X 298.0
#define MIN_X 0.0
#define MAX_Y 90.0
#define MIN_Y -40.0
#define MAX_Z 44.0
#define MIN_Z 0.0

#define INIT_X 0.0
#define INIT_Y 90.0
#define INIT_Z 44.0

#define START_X 146.0
#define START_Y 43.0
#define START_Z 0.0

#define SCAN_DELAY 5    //in seconds
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct _coordinate{
    float x;
    float y;
    float z;
}coordinate;

typedef struct _operating_status{
    coordinate curr_position;
    bool spindle_status;
    float speed;
}operation_status;

void init_operation_status(operation_status* op);
void print_operation_status(operation_status* op);
float set_next_speed(float curr_speed);
void change_operation_status(operation_status* op, float _x, float _y, float _z);

#endif

