#ifndef OPERATION_H_
#define OPERATION_H_

#define CM 10
#define MM 1

#define MAX_X
#define MIN_X
#define MAX_Y
#define MIN_Y
#define MAX_Z
#define MIN_Z

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

#endif