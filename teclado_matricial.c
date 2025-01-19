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

const char key_map[ROWS][COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

char teclado_get(void);
void teclado_init (void);

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

void teclado_init (void){
    int i;
    for(i = 0; i < ROWS; i++){
        gpio_init(pin_rows[i]);
        gpio_set_dir(pin_rows[i], GPIO_OUT);
    }

    for(i = 0; i < COLUMNS; i++){
        gpio_init(pin_columns[i]);
        gpio_set_dir(pin_columns[i], GPIO_IN);
        gpio_pull_down(pin_columns[i]);
    }

}

char teclado_get(void){
    int r, c;
    for (r = 0; r < ROWS; r++){
        gpio_put(pin_rows[r], true);
        for (c = 0; c < COLUMNS; c++){
            if(gpio_get(pin_columns[c])){
                gpio_put(pin_rows[r], false);
                return key_map[r][c];
            }
        }
        gpio_put(pin_rows[r], false);
    }
    return '\0';
}

