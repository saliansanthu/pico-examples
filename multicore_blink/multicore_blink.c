#include "stdio.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h"

const uint8_t led_pin = 25;

void core1_irq_handler(){
    while (multicore_fifo_rvalid())
    {
       if(multicore_fifo_pop_blocking() == 1) gpio_put(led_pin, true);
       else gpio_put(led_pin, false);
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

int main(void){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    stdio_init_all();
    multicore_launch_core1(core1_entry);
    while (true)
    {
       multicore_fifo_push_blocking(1);
       sleep_ms(500);
       multicore_fifo_push_blocking(0);
       sleep_ms(500);
       multicore_fifo_push_blocking(1);
       sleep_ms(1000);
       multicore_fifo_push_blocking(0);
       sleep_ms(1000);
       multicore_fifo_push_blocking(1);
       sleep_ms(2000);
       multicore_fifo_push_blocking(0);
       sleep_ms(2000);
       multicore_fifo_push_blocking(1);
       sleep_ms(3000);
       multicore_fifo_push_blocking(0);
       sleep_ms(3000);
       multicore_fifo_push_blocking(1);
       sleep_ms(4000);
       multicore_fifo_push_blocking(0);
       sleep_ms(4000);
       multicore_fifo_push_blocking(1);
       sleep_ms(5000);
       multicore_fifo_push_blocking(0);
       sleep_ms(5000);
    }
    
}

