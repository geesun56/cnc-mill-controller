/**************************************************
* Penn State University
* On 11/11/2019
* By Geesun Jang
* 
***************************************************/

/*
* Minimum distance range 0.1mm to 10mm
*/

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
        printf("Enter commands (m: manual control / s:scan program) \n");  
        char ch = get_pressed_key();
        int pinno = decode_pin(ch);
        trigger_GPIO_pin(io, OK, QUICK_PUSH ,QUICK_REST, &op);
        
        if(ch == 'm'){
              manual_control(io, &op);
              printf("Exit manual cotrol...\n");
        }else if(ch=='s'){
                printf("Initiailize point\n");
                move_to_start_point(io, &op);
                
                square_range_scan(io, &op);
                
                
                
                //print_operation_status(&op);
                
            
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





