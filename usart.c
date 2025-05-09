#include "USART.h"

/**********USART por hardware**********/
void USART_Init(long baud_rate)
{
    float temp;
    TRISC6 = 0;  // TX como salida
    TRISC7 = 1;  // RX como entrada
    temp = Baud_value;
    SPBRG = (int)temp;
    TXSTA = 0x20;  // Habilita transmisión
    RCSTA = 0x90;  // Habilita recepción y el puerto serial
}

void USART_TxChar(char out)
{
    while (TXIF == 0);  // Espera a que TXREG esté listo
    TXREG = out;
}

char USART_RxChar()
{
    while (RCIF == 0);  // Espera recepción
    if (RCSTAbits.OERR) {
        CREN = 0;
        NOP();
        CREN = 1;
    }
    return RCREG;
}

void USART_SendString(const char *out)
{
    while (*out != '\0') {
        USART_TxChar(*out++);
    }
}

/**********USART por software**********/
void Soft…
