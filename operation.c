#include "operation.h"


void init_operation_status(operation_status* op){
    op->speed = CM;
    op->curr_position.x = 0;
    op->curr_position.y = 0;
    op->curr_position.z = 0;
    op->spindle_status = false;
}

void print_operation_status(operation_status* op){

    printf("<Operation status>\n");
    printf("Operation speed : %0.1f\n", op->speed);
    printf("X axis : %0.1f\n", op->curr_position.x);
    printf("Y axis : %0.1f\n", op->curr_position.y);
    printf("Z axis : %0.1f\n", op->curr_position.z);
    printf("Spindle status: %s\n", op->spindle_status ? "Working": "Idle");

}

float set_next_speed(float curr_speed){
    if (curr_speed == 10){
        return 0.1;
    }else if(curr_speed== 5){
        return 10;
    }else if(curr_speed== 1){
        return 5;
    }else{
        return 1;
    }
}
