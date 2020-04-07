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
    
    

    io = import_registers();
    
  if (io != NULL)
  {
    
    //printf( "mem at 0x%8.8X\n", (unsigned int)io ); /* print where the I/O memory was actually mapped to */
    
    init_GPIO_pins(io); // Set initial state
    reset_controller(io, &op);
    init_operation_status(&op);
    
      while (!done){
            printf("Enter commands (m: manual control / s:scan program / q:quit program / i:set initial state) \n");  
            char ch = get_pressed_key();
            int pinno = decode_pin(ch);
            trigger_GPIO_pin(io, OK, QUICK_PUSH ,QUICK_REST, &op);
            printf("ch check %c\n", ch);
            
                if(ch == 'm'){
                      manual_control(io, &op);
                }      
                if(ch == 'i'){
                      float x_axis;
                      float y_axis;
                      float z_axis;
                      printf("Type location data : ");
                      scanf("%f %f %f", &x_axis, &y_axis, &z_axis);
                      change_operation_status(&op, x_axis, y_axis, z_axis);
                      print_operation_status(&op);
                      
                      
                }else if(ch=='s'){
                        printf("Initiailize point\n");
                        move_to_start_point(io, &op);
                        
                        bool scan_done = false;
                        
                        printf("Start scanning(y/n)? \n");
                        char st= get_pressed_key();
                            
                        if(st == 'y')     square_range_scan(io, &op);
                        
                }else if(ch=='t'){
                        /*coordinate test;
                        test.x = 1;
                        test.y = 100;
                        test.z = 40;
                        
                        int test_result = position_compare(&(op.curr_position),&test);
                        
                        printf("TEST result %d\n", test_result);*/
                
                }else   done = true;
            
        }
        
            printf("Exit machine... \n");
            exit_machine(io,&op);
          
            
        }
  else
  {
    printf("Import registers error");
  }

  return 0;
}





