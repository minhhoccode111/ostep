
all: measuring_system_call measuring_context_switch


clean:
	rm -f measuring_system_call measuring_context_switch

measuring_system_call: measuring_system_call.c
	gcc -o measuring_system_call measuring_system_call.c -Wall

measuring_context_switch: measuring_context_switch.c
	gcc -o measuring_context_switch measuring_context_switch.c -Wall

