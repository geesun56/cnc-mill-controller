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