#pragma config PLLDIV = 2, CPUDIV = OSC1_PLL2, USBDIV = 1
#pragma config FOSC = INTOSC_EC, FCMEN = OFF, IESO = OFF
#pragma config PWRT = OFF, BOR = OFF, BORV = 3, VREGEN = OFF
#pragma config WDT = OFF
#pragma config WDTPS = 32768
#pragma config CCP2MX = ON, PBADEN = OFF, LPT1OSC = OFF, MCLRE = ON
#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
#pragma config CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
#pragma config EBTRB = OFF

#define _XTAL_FREQ 8000000 

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "DS1307.h"
#include "USART.h"
#include "lcd.h"                        // Libreria de la pantalla lcd
#include "dht11.h"                      // Libreria del sensor DHT11
#include "I2C.h"

// Variables del sistema
// Variables de sensores
float temperatura = 0.0, humedad = 0.0;
char dht_ok = 0;

// Variables de reloj
unsigned char hour, min, sec, day, month, year, dow;

// Buffers
char buffer[32];
char comando;
int sistema_activo = 0;

// Variables GPS simuladas
char latitud[] = "Lat: 19.4326";
char altitud[] = "Alt: 2240m";
void main()
{
    OSCCON = 0b01110000; // Oscilador interno 8 MHz
    ADCON1bits.PCFG = 0x0F; // Pines digitales
	TRISCbits.TRISC0 = 0;
    LATCbits.LATC0 = 1;
    __delay_ms(500);
    LATCbits.LATC0 = 0;
    Lcd_Init();
    USART_Init(9600);        // Bluetooth por hardware (RC6/RC7)
    SoftUSART_Init();        // GPS por software (ej. RD0/RD1)
    DS1307_Init();           // Inicializa reloj

    while (1)
    {
        // Escucha comandos del Bluetooth
        if (PIR1bits.RCIF)
        {
            comando = USART_RxChar();
            if (comando == '1') sistema_activo = 1;
            if (comando == '0') sistema_activo = 0;
        }

        if (sistema_activo)
        {
            // ----------- TEMPERATURA y HUMEDAD -------------
            dht_ok = DHT11_Read_Data(&temperatura, &humedad);
            if (dht_ok == 1)
            {
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                sprintf(buffer, "Hum: %0.1f %%", humedad);
                Lcd_Write_String(buffer);
                Lcd_Set_Cursor(2,1);
                sprintf(buffer, "Tem: %0.1f C", temperatura);
                Lcd_Write_String(buffer);
                __delay_ms(2000);
            }

            // --------------- FECHA y HORA -------------------
            DS1307_GetDateTime(&day, &month, &year, &dow, &hour, &min, &sec);
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            sprintf(buffer, "%02u/%02u/%02u", day, month, year);
            Lcd_Write_String(buffer);
            Lcd_Set_Cursor(2,1);
            sprintf(buffer, "%02u:%02u:%02u", hour, min, sec);
            Lcd_Write_String(buffer);
            __delay_ms(2000);

            // ------------------- GPS ------------------------
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(latitud);   // Aquí iría la lectura real del GPS
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String(altitud);
            __delay_ms(2000);
        }
        else
        {
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Sistema Inactivo");
            __delay_ms(1000);
        }
    }
}
