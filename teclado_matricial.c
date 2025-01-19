#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"

#define ROWS 4
#define COLUMNS 4
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BUZZER 21

#define SLICE_GPIO10 2
#define CHANNEL_GPIO10 PWM_CHAN_B
#define TOP 8877
#define DIV 32

//pinos de linhas e colunas do teclado matricial
const uint8_t pin_rows[ROWS] = {2, 3, 4, 5};
const uint8_t pin_columns[COLUMNS] = {16, 17, 18, 19};

//matriz de mapeamento dos botões do teclado matricial
const char key_map[ROWS][COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//protótipo das funções
char teclado_get(void);
void teclado_init (void);
void led_rgb_init(void);
void liga_led_rgb(bool red, bool green, bool blue);
void buzzer_init(void);


int main()
{
    char tecla;
    //inicializa os pinos dos periféricos utilizados
    teclado_init();
    led_rgb_init();
    buzzer_init();

    //inicializa comunicação serial
    stdio_init_all();

    while (true) {
        //lê teclado
        tecla = teclado_get();
        switch (tecla)
        {
        case '1':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;
        
        case '2':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case '3':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;
        
        case '4':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case '5':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case '6':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case '7':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case '8':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case '9':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case '0':
            printf("A tecla %c foi pressionada.\n", tecla);
            sleep_ms(250);
            break;

        case 'A':
            //liga led vermelho
            liga_led_rgb(1,0,0);
            break;

        case 'B':
            //liga led verde
            liga_led_rgb(0,1,0);
            break;

        case 'C':
            //liga led azul
            liga_led_rgb(0,0,1);
            break;

        case 'D':
            //liga todos os leds
            liga_led_rgb(1,1,1);
            break;

        case '*':
            //entra em modo de armazenamento USB
            reset_usb_boot(0,0);
            break;

        case '#':
            //emite som no buzzer durante 1s
            pwm_set_chan_level(SLICE_GPIO10, CHANNEL_GPIO10, (TOP + 1)/2); //dutty cycle de 50%
            sleep_ms(1000);
            pwm_set_chan_level(SLICE_GPIO10, CHANNEL_GPIO10, 0);
            break;

        default:
            //delay diminuir o travamento na simulação
            sleep_ms(1);
            break;
        }
        
    }
}

//função para inicializar os pinos do teclado matricial
void teclado_init (void){
    int i;
    //inicializa os pinos de linha do teclado matricial como saída
    for(i = 0; i < ROWS; i++){
        gpio_init(pin_rows[i]);
        gpio_set_dir(pin_rows[i], GPIO_OUT);
    }

    //inicializa os pinos de coluna do teclado matricial como entrada
    for(i = 0; i < COLUMNS; i++){
        gpio_init(pin_columns[i]);
        gpio_set_dir(pin_columns[i], GPIO_IN);
        gpio_pull_down(pin_columns[i]);
    }

}

//função para ler tecla pressionada
char teclado_get(void){
    int r, c;
    for (r = 0; r < ROWS; r++){
        //coloca sinal de tensão alto nos pinos de linha do teclado
        gpio_put(pin_rows[r], true);
        //varre as colunas de 1 a 4 do teclado testando se algum botão na linha atual foi precionado
        for (c = 0; c < COLUMNS; c++){
            //se precionado retorna o caractere correspondente ao botão
            if(gpio_get(pin_columns[c])){
                gpio_put(pin_rows[r], false);
                return key_map[r][c];
            }
        }
        gpio_put(pin_rows[r], false);
    }
    //se nenhum botão for precionado retorna caractere nulo
    return '\0';
}

//função para inicializar os pinos do led rgb
void led_rgb_init(void){
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);

    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
}

//função para ligar leds selecionados por 1s
void liga_led_rgb(bool red, bool green, bool blue){
    gpio_put(LED_RED, red);
    gpio_put(LED_GREEN, green);
    gpio_put(LED_BLUE, blue);
    sleep_ms(1000);
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
}

//função para inicializar o pwm do buzzer
void buzzer_init(void){
    //inicializa o pino do buzzer como pwm
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    //seta valor máximo de contagem do PWM (TOP)
    pwm_set_wrap(SLICE_GPIO10, TOP);
    //seta valor de divisão do clock do PWM
    pwm_set_clkdiv(SLICE_GPIO10, DIV);

    /*
    valor de TOP e DIV previamente calculado para emitir som da nota LÁ 4 (440 Hz): 
    f_pwm = f_sys /((TOP + 1) * (DIV) * (CSR_PH_CORRECT + 1)) ~ 440 
    .: CSR_PH_CORRECT não setado -> 0
    */

    //seta valor inicial de dutty cycle como 0
    pwm_set_chan_level(SLICE_GPIO10, CHANNEL_GPIO10, 0);
    //abilita PWM
    pwm_set_enabled(SLICE_GPIO10, true);
}
