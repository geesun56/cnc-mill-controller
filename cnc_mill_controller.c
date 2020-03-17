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
        printf("Enter commands (m: manual control / s:execute program) \n");  
        char ch = get_pressed_key();
        int pinno = decode_pin(ch);
        trigger_GPIO_pin(io, OK, QUICK_PUSH ,QUICK_REST, &op);
        
        if(ch == 'm'){
              manual_control(io, &op);
              printf("Exit manual cotrol...\n");
            }else if(ch=='s'){
                printf("Initiailize point\n");

                speed_change(&op, io, 5.0);
                
                trigger_GPIO_pin(io, XPLUS, QUICK_PUSH , QUICK_REST, &op);
                
                trigger_GPIO_pin(io, YMINUS, QUICK_PUSH , QUICK_REST, &op);
                
                trigger_GPIO_pin(io, ZMINUS, QUICK_PUSH , QUICK_REST, &op);
                
                trigger_GPIO_pin(io, ZPLUS, QUICK_PUSH , QUICK_REST, &op);
                
                trigger_GPIO_pin(io, YPLUS, QUICK_PUSH , QUICK_REST, &op);
                
                trigger_GPIO_pin(io, XMINUS, QUICK_PUSH , QUICK_REST, &op);
                
                //print_operation_status(&op);
                
            }else if(ch=='p'){
              coordinate tar;
              tar.x = 10;
              tar.y = 100;
              tar.z = 30;
              
              move_to_point(io, &op, &tar);
            }else{
              done = true;
              printf("Exit machine... \n");
              exit_machine(io,&op);
            }
            
          }

          
            
        }
  else
  {
    printf("Import registers error");
  }

  return 0;
}





