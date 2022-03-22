#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/multicore.h"
#include "hardware/irq.h"


#define MISO 16
#define CS 17
#define SCLK 18
#define MOSI 19

#define SPI_PORT spi0


void core1_irq_handler(){
    while (multicore_fifo_rvalid())
    {
       uint8_t count = multicore_fifo_pop_blocking();
       printf("From 2nd core -> %d\n", count);
    }
    multicore_fifo_clear_irq(); 
}

void core1_entry(){
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_irq_handler);
    irq_set_enabled(SIO_IRQ_PROC1, true);

    while(true){
        tight_loop_contents();
    }
}

int main(){
    stdio_init_all();
    spi_init(SPI_PORT, 500000);

    spi_set_slave(SPI_PORT, true);


    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(SCLK, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);
    gpio_set_function(CS, GPIO_FUNC_SPI);

    uint8_t count = 0;

    multicore_launch_core1(core1_entry);

    while(1){
        spi_read_blocking(SPI_PORT, 0, (uint8_t *) &count, 1);
        multicore_fifo_push_blocking(count);
    }
}