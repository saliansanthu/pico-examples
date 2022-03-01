#include "stdio.h"
#include "pico/stdlib.h"

bool isPrime(int n){
    if (n <= 1) return false;

    for(int i = 2; i <= sqrt(n); i++)
        if( n % i == 0) return false;
    
    return true;
}

int main(){
    stdio_init_all();
    while (true)
    {
        sleep_ms(10000);
        printf("/ Prime numbers / \n");
        for(int i = 2; i <= 100; i++)
            if (isPrime(i)){
                printf("%d \n", i);
                sleep_ms(1000);
            }
    }
    
    return 0;
}