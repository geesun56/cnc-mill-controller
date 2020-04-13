TARGET=cnc_mill_controller

SOURCES=./starter_codes/import_registers.c \
	./starter_codes/standard_input.c \
        ./starter_codes/enable_pwm_clock.c \
		./manual_control.c \
		./axis_control.c\
		./operation.c\
		./trigger.c\
		cnc_mill_controller.c

OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(OBJECTS)
	gcc $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

%.o:%.c
	gcc -c $< -o $@
