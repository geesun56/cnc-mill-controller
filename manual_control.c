#include "manual_control.h"


void manual_control(volatile struct io_peripherals *io, operation_status* op){

    bool done = false;

    
    printf("*****************************************************\n");
    printf("*************  MANUAL CONTROL MODE ******************\n");
    printf("*****************************************************\n");
    printf("*      w(Y+)           t(z+)                        *\n");
    printf("* a(X-)     d(X+)      g(z-)      j(OK) k(EXIT)     *\n");
    printf("*      x(Y-)                                        *\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");


    while(!done){
        char ch = get_pressed_key();
        int pinno = decode_pin(ch);

        if(pinno == -1){
            done = true;
            printf("Quit manual control...\n");
        }else{
            trigger_GPIO_pin(io, pinno, QUICK_PUSH ,QUICK_REST, op);
            print_operation_status(op);
        }

    }

    
}