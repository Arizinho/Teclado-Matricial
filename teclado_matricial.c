#include <stdio.h>

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
    char tecla;
    teclado_init();
    while (true) {
        tecla = teclado_get();
        switch (tecla)
        {
        case '1':
            /* code */
            break;
        
        case '2':
            /* code */
            break;

        case '3':
            /* code */
            break;
        
        case '4':
            /* code */
            break;

        case '5':
            /* code */
            break;

        case '6':
            /* code */
            break;

        case '7':
            /* code */
            break;

        case '8':
            /* code */
            break;

        case '9':
            /* code */
            break;

        case '0':
            /* code */
            break;

        case 'A':
            liga_led_rgb(1,0,0);
            break;

        case 'B':
            liga_led_rgb(0,1,0);
            break;

        case 'C':
            liga_led_rgb(0,0,1);
            break;

        case 'D':
            liga_led_rgb(1,1,1);
            break;

        case '*':
            /* code */
            break;

        case '#':
            /* code */
            break;

        default:
            break;
        }
        
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

void led_rgb_init(void){
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);

    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
}

void liga_led_rgb(bool red, bool green, bool blue){
    gpio_put(LED_RED, red);
    gpio_put(LED_GREEN, green);
    gpio_put(LED_BLUE, blue);
    sleep_ms(1000);
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
}