#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "operation.h"
#include "pin_config.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "starter.h"
#include "axis_control.h"


void manual_control(volatile struct io_peripherals *io, operation_status* op);