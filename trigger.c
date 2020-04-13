#include "trigger.h"


void trigger_generate(volatile struct io_peripherals *io, float trig, float interval){
	int i = 0;
	
	while(i < 10000){    
		GPIO_SET(&(io->gpio), TRIGGER);
		usleep(1000);
		GPIO_CLR(&(io->gpio), TRIGGER);
		usleep(1000);
		GPIO_SET(&(io->gpio), TRIGGER);
		usleep(1000);
		GPIO_CLR(&(io->gpio), TRIGGER);
		usleep(40000);
		i++;
	}

}
