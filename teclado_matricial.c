#include <stdio.h>
#include "pico/stdlib.h"

#define ROWS 4
#define COLUMNS 4
#define LED_RED 12
#define LED_GREEN 13
#define LED_BLUE 14
#define BUZZER 10

const uint8_t pin_rows[ROWS] = {2, 3, 4, 5};
const uint8_t pin_columns[COLUMNS] = {16, 17, 18, 19};


int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
