#include "trigger.h"


void trigger_generate(volatile struct io_peripherals *io, float freq, int freq_unit, int pulses){
	
	int duration = (1/(freq))*80;
	
	int i = 0;
	int j = 0;
	printf("Trig duration: %d pulses: %d\n", duration, pulses);
	
	while(j < 100000){
		i = 0;
		while(i < pulses){    
			GPIO_SET(&(io->gpio), TRIGGER);
			for(int k = 0; k<duration; k++);
			GPIO_CLR(&(io->gpio), TRIGGER);
			usleep(130);
			
			i++;
		}
		
		usleep(5);
		j++;
	}

}
