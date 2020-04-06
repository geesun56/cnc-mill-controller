#include "axis_control.h"


void init_GPIO_pins(volatile struct io_peripherals *io){
    
    /* * * Initialize GPIO pins for the CNC mill controller * * */
    
    GPIO_CLR( &(io->gpio), ZPLUS );
    GPIO_CLR( &(io->gpio), ZMINUS );
    GPIO_CLR( &(io->gpio), YPLUS );
    GPIO_CLR( &(io->gpio), YMINUS );
    GPIO_CLR( &(io->gpio), XPLUS );
    GPIO_CLR( &(io->gpio), XMINUS );
    GPIO_CLR( &(io->gpio), OK );
    GPIO_CLR( &(io->gpio), EXIT );
    
    io->gpio.GPFSEL0.field.FSEL6 = GPFSEL_INPUT;    //set GPIO06 as OK
    io->gpio.GPFSEL2.field.FSEL1 = GPFSEL_INPUT;    //set GPIO12 as EXIT
    io->gpio.GPFSEL1.field.FSEL3 = GPFSEL_INPUT;    //set GPIO13 as XPLUS
    io->gpio.GPFSEL1.field.FSEL6 = GPFSEL_INPUT;    //set GPIO16 as YMINUS
    io->gpio.GPFSEL1.field.FSEL9 = GPFSEL_INPUT;    //set GPIO19 as YPLUS
    io->gpio.GPFSEL2.field.FSEL3 = GPFSEL_INPUT;    //set GPIO20 as ZMINUS
    io->gpio.GPFSEL2.field.FSEL4 = GPFSEL_INPUT;    //set GPIO21 as XMINUS
    io->gpio.GPFSEL2.field.FSEL2 = GPFSEL_INPUT;    //set GPIO26 as ZPLUS
    
    
    
   
}

void trigger_GPIO_pin(volatile struct io_peripherals *io, int pinno, int trigger_time, int rest_time, operation_status* op){

        if(AC_DEBUG){ printf("Trigger Pin No. %d \n",pinno); }

        if(range_check(op, pinno)){       

            if (pinno == OK){
            io->gpio.GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;
            }else if(pinno == EXIT){
                io->gpio.GPFSEL2.field.FSEL1 = GPFSEL_OUTPUT;
            }else if(pinno == XPLUS){
                io->gpio.GPFSEL1.field.FSEL3 = GPFSEL_OUTPUT;
            }else if(pinno == YMINUS){
                io->gpio.GPFSEL1.field.FSEL6 = GPFSEL_OUTPUT;
            }else if(pinno == YPLUS){
                io->gpio.GPFSEL1.field.FSEL9 = GPFSEL_OUTPUT;
            }else if(pinno == ZMINUS){
                io->gpio.GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;
            }else if(pinno == XMINUS){
                io->gpio.GPFSEL2.field.FSEL4 = GPFSEL_OUTPUT;
            }else{
                io->gpio.GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;
            }
        
            usleep(trigger_time);
        
            if (pinno == OK){
                io->gpio.GPFSEL0.field.FSEL6 = GPFSEL_INPUT;
                op->spindle_status = !(op->spindle_status);
            }else if(pinno == EXIT){
                io->gpio.GPFSEL2.field.FSEL1 = GPFSEL_INPUT;
                op->speed = set_next_speed(op->speed);
            }else if(pinno == XPLUS){
                io->gpio.GPFSEL1.field.FSEL3 = GPFSEL_INPUT;
                op->curr_position.x += 1*(op->speed);
            }else if(pinno == YMINUS){
                io->gpio.GPFSEL1.field.FSEL6 = GPFSEL_INPUT;
                op->curr_position.y -= 1*(op->speed);
            }else if(pinno == YPLUS){
                io->gpio.GPFSEL1.field.FSEL9 = GPFSEL_INPUT;
                op->curr_position.y += 1*(op->speed);
            }else if(pinno == ZMINUS){
                io->gpio.GPFSEL2.field.FSEL3 = GPFSEL_INPUT;
                op->curr_position.z -= 1*(op->speed);
            }else if(pinno == XMINUS){
                io->gpio.GPFSEL2.field.FSEL4 = GPFSEL_INPUT;
                op->curr_position.x -= 1*(op->speed);
            }else{
                io->gpio.GPFSEL2.field.FSEL2 = GPFSEL_INPUT;
                op->curr_position.z += 1*(op->speed);
            }
            
            usleep(rest_time); 

            if(AC_DEBUG)    print_operation_status(op);
        }else{
            printf("Invalid command\n");
        }
  
}

void hold_GPIO_pin(volatile struct io_peripherals *io, int pinno){
    
    
    if (pinno == EXIT){
        io->gpio.GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;
    }else{
        printf("Do not hold this button\n");
    }
    
    usleep(300000);
    
    if (pinno == EXIT){
        io->gpio.GPFSEL0.field.FSEL6 = GPFSEL_INPUT;
    }else{
        printf("Do not hold this button\n");
    }
    
    usleep(10000);
    
}

int decode_pin(char ch){
    int target_pin = 0;
    
    switch(ch){
        case 'w':
            target_pin = YPLUS;
            break;
        case 'x':
            target_pin = YMINUS;
            break;
        case 'd':
            target_pin = XPLUS;
            break;
        case 'a':
            target_pin = XMINUS;
            break;
        case 't':
            target_pin = ZPLUS;
            break;
        case 'g':
            target_pin = ZMINUS;
            break;
        case 'j':
            target_pin = OK;
            break;
        case 'k':
            target_pin = EXIT;
            break;
        default:
            target_pin = -1;
    }
    
    return target_pin;
        
            
}

int range_check(operation_status* op, int pinno){
        
        if(pinno == ZPLUS){
            if(op->curr_position.z + (op->speed) <= MAX_Z )   return 1;
            else    return 0;
        }else if(pinno == ZMINUS){
            if(op->curr_position.z - (op->speed) >= MIN_Z )   return 1;
            else    return 0;
        }else if(pinno == XPLUS){
            if(op->curr_position.x + (op->speed) <= MAX_X )   return 1;
            else    return 0;
        }else if(pinno == XMINUS){
            if(op->curr_position.x - (op->speed) >= MIN_X )   return 1;
            else    return 0;
        }else if(pinno == YPLUS){
            if(op->curr_position.y + (op->speed) <= MAX_Y )   return 1;
            else    return 0;
        }else if(pinno == YMINUS){
            if(op->curr_position.y - (op->speed) >= MIN_Y )   return 1;
            else    return 0;
        }else{
            return 1;
        }
}

void speed_change(operation_status * op, volatile struct io_peripherals *io, float request_speed){
    float speed_table[4] = {0.1, 1.0, 5.0, 10.0};
    int curr_idx;
    int tar_idx;
    int times;

    for(int i = 0; i<4; i++){
        if(speed_table[i] == op->speed) curr_idx = i;
        if(speed_table[i] == request_speed) tar_idx = i;
    }

    if(op->speed < request_speed){
        times = tar_idx - curr_idx;
    }
    else if(op->speed > request_speed){
        times = 4 - curr_idx + tar_idx;
    }else{
        times = 0;
    }

    for(int i=0; i<times; i++){
        trigger_GPIO_pin(io, EXIT, QUICK_PUSH, QUICK_REST, op);
    }

}

void move_to_point(volatile struct io_peripherals *io, operation_status * op, coordinate* target_point){
  float* curr_point = (float*)&(op->curr_position);
  float* tar_point = (float*)target_point;
  char axis_array[3] = {'x', 'y', 'z'};

  for(int i=0; i<3; i++){
      int dist = *tar_point - *curr_point;
      if(dist > 0){
          _axis_move(io, op, axis_array[i], 1, dist);
      }else if(dist < 0){
          _axis_move(io, op, axis_array[i], 0, -dist);
      }else{

      }

      tar_point++;
      curr_point++;
  }
  
}

void _axis_move (volatile struct io_peripherals *io, operation_status * op, char axis, int dir, int distance)
{
  int _target_pin;

  if(axis == 'x'){
      if(dir) _target_pin = XPLUS;
      else  _target_pin = XMINUS;
  }else if(axis == 'y'){
      if(dir) _target_pin = YPLUS;
      else  _target_pin = YMINUS;
  }else if(axis == 'z'){
      if(dir) _target_pin = ZPLUS;
      else  _target_pin = ZMINUS;
  }else{
    printf("Invalid axis move\n");
    return;    
  }

  printf("axis: %c, pinno: %d , dist: %d\n", axis, _target_pin, distance);

  speed_change(op, io, 1.0);

  for(int i=0 ; i<distance ; i++){
      trigger_GPIO_pin(io, _target_pin, QUICK_PUSH, QUICK_REST, op);
  }

}

void exit_machine(volatile struct io_peripherals *io, operation_status * op){
    coordinate _initial_point;
    _initial_point.x = MIN_X;
    _initial_point.y = 0;
    _initial_point.z = MAX_Z;
    
    coordinate _zaxis;
    _zaxis.x = op->curr_position.x;
    _zaxis.y = op->curr_position.y;
    _zaxis.z = MAX_Z;
    
    move_to_point(io, op,&_zaxis );
    move_to_point(io, op, &_initial_point);
    
    trigger_GPIO_pin(io, EXIT, LONG_PUSH, QUICK_REST, op);
}

void square_range_scan(volatile struct io_peripherals *io, operation_status * op){
    
    float scan_length;
    float scan_step;

    printf("Type scan area length(mm): ");
    scanf("%f", &scan_length);
    printf("Type scan unit distance(0.1mm/1mm/5mm/10mm):");
    scanf("%f", &scan_step);


    int half_length = scan_length/2;
    int steps = scan_length/scan_step;
    printf("* Start square area scanning *");
    printf("- scan area: %0.1f mm^2\n", scan_length);
    printf("- scan step: %0.1f mm^2\n", scan_step);
    printf("- scan points: %d X %d\n", steps, steps);

    coordinate origin_point;
    origin_point.x = op->curr_position.x;
    origin_point.y = op->curr_position.y;
    origin_point.z = op->curr_position.z;

    coordinate start_point;
    start_point.x = op->curr_position.x - half_length;
    start_point.y = op->curr_position.y + half_length;
    start_point.z = 0;

    move_to_point(io,op, &start_point);
    speed_change(op,io, scan_step);

    for(int i=0; i<steps; i++){
        
        for(int i=0; i<steps; i++){
            trigger_GPIO_pin(io, XPLUS, QUICK_PUSH, QUICK_REST, op);
        }

        start_point.y--;
        move_to_point(io,op, &start_point);
    }
    printf("Scanning completed!");

    move_to_point(io,op, &origin_point);
}

void move_to_start_point(volatile struct io_peripherals *io, operation_status * op){
    coordinate scan_start_point;
    scan_start_point.x = START_X;
    scan_start_point.y = START_Y;
    scan_start_point.z = START_Z;
    
    coordinate initial_start_point;
    initial_start_point.x = INIT_X;
    initial_start_point.y = INIT_Y;
    initial_start_point.z = INIT_Z;
    
    int _state_check1 = position_compare(&initial_start_point, &(op->curr_position));
    int _state_check2 = position_compare(&scan_start_point, &(op->curr_position));
    
    if(_state_check1){
        speed_change(op, io, 10.0);

        for(int i=0; i<14; i++){
            trigger_GPIO_pin(io, XPLUS, QUICK_PUSH, LONG_REST, op);
        }
        
        trigger_GPIO_pin(io, YPLUS, QUICK_PUSH, LONG_REST, op);
        
    }
    
    if(!_state_check2)  move_to_point(io,op, &scan_start_point);
    
}

bool position_compare(coordinate* p1, coordinate* p2){
        if(p1->x == p2->x && p1->y == p2->y && p1->z == p2->z) return true;
        else return false;
}
