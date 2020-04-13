#include "pin_config.h"
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "./starter_codes/cm.h"
#include "./starter_codes/gpio.h"
#include "./starter_codes/io_peripherals.h"




#define TRIG_TIME 10
#define INTVAL_TIME 20

void trigger_generate(volatile struct io_peripherals *io, float trig, float interval);
