#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"


#define MISO 16
#define CS 17
#define SCLK 18
#define MOSI 19

#define SPI_PORT spi0

int main(){
    stdio_init_all();
    spi_init(SPI_PORT, 500000);

    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(SCLK, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);

    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);
    gpio_put(CS, 1);

    uint8_t count = 0;

    while(1){
        gpio_put(CS, 0);
        spi_write_blocking(SPI_PORT, (uint8_t *) &count, 1);
        gpio_put(CS, 1);

        printf("Master -> %d \n", count);
        count++;

        sleep_ms(500);
    }
}