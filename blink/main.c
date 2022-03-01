#include <stdlib.h>
#include "pico/stdlib.h"

int main(){

    const uint led_pin = 25;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    stdio_init_all();

    while(1){
        printf("LED -> ON \n");
        gpio_put(led_pin, true);
        sleep_ms(10000);
        printf("LED -> OFF \n");
        gpio_put(led_pin, false);
        sleep_ms(10000);
    }
}