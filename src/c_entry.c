#include<stdint-gcc.h>

void init_uart();
void dragon_putc(const char c);
void put_line(char*);

void quit()
{
    volatile uint32_t *reset_reg = (uint32_t*)0x4ab000;

    *reset_reg = 0x0;
}

uint32_t wait_array[4];

void c_entry(uint32_t cpu_id)
{

    // We do a message passing dance:
    // cpu0 --> cpu1 --> cpu2 --> cpu3 --> reset!

    if(cpu_id == 0){
        put_line("cpu0: Hello World!\n");

        wait_array[0] = 1;
        __asm("dsb sy");
    }

    if(cpu_id == 1){

        while(wait_array[0] == 0);
        put_line("cpu1: Hello World!\n");
        wait_array[1] = 1;
        __asm("dsb sy");
    }

    if(cpu_id == 2){

        while(wait_array[1] == 0);
        put_line("cpu2: Hello World!\n");
        wait_array[2] = 1;
        __asm("dsb sy");
    }

    if(cpu_id == 3){
        while(wait_array[2] == 0);
        put_line("cpu3: Hello World!\n");

        quit();
    }
}


void put_line(char* line_c){

    while(*line_c){
        dragon_putc(*line_c);
        line_c++;
    }

}
