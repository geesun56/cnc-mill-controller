#include "pin_config.h"
#include "operation.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "./starter_codes/cm.h"
#include "./starter_codes/gpio.h"
#include "./starter_codes/io_peripherals.h"
#include "./starter_codes/spi.h"
#include "./starter_codes/pwm.h"

#define AC_DEBUG 0

void init_GPIO_pins(volatile struct io_peripherals *io);
void trigger_GPIO_pin(volatile struct io_peripherals *io, int pinno, int trigger_time, int rest_time, operation_status* op);
int decode_pin(char ch);
void hold_GPIO_pin(volatile struct io_peripherals *io, int pinno);
int range_check(operation_status* op, int pinno);
void speed_change(operation_status * op, volatile struct io_peripherals *io, float request_speed);