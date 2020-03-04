/**************************************************
* Penn State University
* On 11/11/2019
* By Geesun Jang
* 
***************************************************/


#include "starter.h"
#include "pin_config.h"
#include "axis_control.h"
#include "manual_control.h"
#include "operation.h"

int main( void )
{
    volatile struct io_peripherals *io;
    operation_status op;
    bool done = false;
    
    init_operation_status(&op);

    io = import_registers();
    
  if (io != NULL)
  {
    
    //printf( "mem at 0x%8.8X\n", (unsigned int)io ); /* print where the I/O memory was actually mapped to */
    init_GPIO_pins(io); // Set initial state
    
      while (!done){
          
          char ch = get_pressed_key();
         int pinno = decode_pin(ch);
          
          if(ch == 'm'){
              manual_control(io, &op);
              done=true;
              printf("Exit manual cotrol...\n");
            }else if(ch=='s'){
                printf("Control program \n");
                print_operation_status(&op);
                trigger_GPIO_pin(io, OK, QUICK_PUSH ,QUICK_REST, &op);
                
                trigger_GPIO_pin(io, EXIT, QUICK_PUSH ,QUICK_REST, &op);
                trigger_GPIO_pin(io, EXIT, QUICK_PUSH ,QUICK_REST, &op);
                
                trigger_GPIO_pin(io, XPLUS, QUICK_PUSH , QUICK_REST, &op);
                trigger_GPIO_pin(io, YMINUS, QUICK_PUSH , QUICK_REST, &op);
                trigger_GPIO_pin(io, ZMINUS, QUICK_PUSH , QUICK_REST, &op);
                
                trigger_GPIO_pin(io, ZPLUS, QUICK_PUSH , QUICK_REST, &op);
                trigger_GPIO_pin(io, XMINUS, QUICK_PUSH , QUICK_REST, &op);
                trigger_GPIO_pin(io, YPLUS, QUICK_PUSH , QUICK_REST, &op);
            }else{
              done = true;
              printf("Input error \n");
            }
            
          }

          
            
        }
  else
  {
    printf("Import registers error");
  }

  return 0;
}




