#include "stdlib.h"
#include "pico/stdlib.h"

int main(){
    stdio_init_all();
    while(true){
        printf("Hello from pico !! \n");
        sleep_ms(1000);
    }
    return 0;
}