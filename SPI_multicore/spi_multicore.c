#include "stdio.h"
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#define 	spi0   ((spi_inst_t * const)spi0_hw)

const uint8_t led_pin = 25;




/////////////////////SPI/////////////////////


////////////////////MULTI CORE//////////////
void core1_irq_handler(){
    while (multicore_fifo_rvalid())
    {
        uint8_t val = multicore_fifo_pop_blocking();
        printf("From stm32 -> %03d\n", val);
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

/////////////////////MAIN//////////////////////
int main(void){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    stdio_init_all();
    //multicore_launch_core1(core1_entry);

    printf("Initializing SPI....\n");
    spi_init(spi0, 48000);
    spi_set_slave(spi0, true);


    int bytesread = 0;
    uint8_t val;
    while (true)
    {
        gpio_put(led_pin, true);
        printf("No data ! \n");
       bytesread = spi_read_blocking(spi_default, 0, (unsigned char *) &val, 1);
       if(bytesread > 0) multicore_fifo_push_blocking(val);
       else printf("No data ! \n");
       sleep_ms(1000);
       gpio_put(led_pin, false);
       sleep_ms(1000);
    }
    
}