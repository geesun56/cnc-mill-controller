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

#define AC_DEBUG 1

void init_GPIO_pins(volatile struct io_peripherals *io);
void trigger_GPIO_pin(volatile struct io_peripherals *io, int pinno, int trigger_time, int rest_time, operation_status* op);
int decode_pin(char ch);
void hold_GPIO_pin(volatile struct io_peripherals *io, int pinno);
int range_check(operation_status* op, int pinno);
void speed_change(operation_status * op, volatile struct io_peripherals *io, float request_speed);

void move_to_point(volatile struct io_peripherals *io, operation_status * op, coordinate* target_point);
void _axis_move (volatile struct io_peripherals *io, operation_status * op, char axis, int dir, int distance);
void exit_machine(volatile struct io_peripherals *io, operation_status * op);
void square_range_scan(volatile struct io_peripherals *io, operation_status * op);

void move_to_start_point(volatile struct io_peripherals *io, operation_status * op);
bool position_compare(coordinate* p1, coordinate* p2);
