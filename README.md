# Teclado Matricial

O projeto está programado para utilizar os pinos GPIOs da Raspberry Pi Pico W com a seguinte configuração: 

| GPIO | Componente | Função |
|------------|------|--------|
| **21** | Buzzer | Sinal PWM para emissão de som |
| **13** | LED Vermelho | Acende o LED vermelho (saída) |
| **11** | LED Verde | Acende o LED verde (saída) |
| **12** | LED Azul | Acende o LED azul (saída) |
| **2, 3, 4, 5** | Linhas do teclado matricial | Envio de sinais para pinos de linha do teclado (saída) |
| **16, 17, 18, 19** | Colunas do teclado matricial | Recebimento de sinais do teclado nos pinos de coluna (entradas com pull-down) |

---

## **Funcionamento do Teclado Matricial**  

| Tecla | Função |
|-------|--------|
| `0-9` | Exibe via comunicação serial qual tecla foi pressionada |
| `A` | Acende o **LED vermelho** |
| `B` | Acende o **LED verde** |
| `C` | Acende o **LED azul** |
| `D` | Acende **todos os LEDs** simultaneamente |
| `#` | Aciona o **buzzer** por 1 segundo |
| `*` | Coloca a Raspberry Pi Pico W em modo de armazenamento |

---

## **Link do Vídeo**  

https://drive.google.com/file/d/1NuUb0r1XfHRgWLQAv0Yj6BlDyNkLGItU/view?usp=drive_link

