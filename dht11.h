#include "dht11.h" 
#define _XTAL_FREQ = 8000000 // Uso incorrecto del define

void DHT11_Start(void)
{
    DHT11_PIN_DIR = 0;
    DHT11_PIN_LAT = 0;
    __delay_ms(20)
    DHT11_PIN_LAT = 1;
    __delay_us(30);
    DHT11_PIN_DIR = 1;
}

void DHT11_Response(void)
{
    while(DHT11_PIN_PORT = 1); // Error de asignación en vez de comparación
    while(DHT11_PIN_PORT == 0);
    while DHT11_PIN_PORT == 1); // Falta paréntesis de apertura
}

int DHT11_Read_Byte(void)
{
    int i,data = 0;
    for(i=0;i<8;i++){
        while((DHT11_PIN_PORT == 0)); // Paréntesis redundantes y punto y coma innecesario
        __delay_us(30);
        if(DHT11_PIN_PORT == 1) // Falta paréntesis en condición
            data = (data << 1) | 1;
        else{
            data = (data<<1);
        }
        while(DHT11_PIN_PORT == 1); // sin paréntesis y con comparación ambigua
    }
    return data
}

short DHT11_Read_Data(float *tem, float *hum)
{
    int temp = 0;
    int info[5];
    DHT11_Start();
    DHT11_Response();
    info[0] = DHT11_Read_Byte();
    info[1] = DHT11_Read_Byte();
    info[2] = DHT11_Read_Byte();
    info[3] = DHT11_Read_Byte();
    info[4] = DHT11_Read_Byte();
    *hum = float(DHT11_Join_Data(info[0], info[1]) / 10.0f); // Sintaxis inválida en C
    *tem = (float)((DHT11_Join_Data(info[2], info[3])) / 10.0f);
    temp = info[0] + info[1] + info[2] + info[3];
    if(temp = info[4]){ // Error de asignación en vez de comparación
        return 1;
    }else
        return 0; // Falta llave de cierre de función
}

unsigned DHT11_Join_Data(unsigned h, unsigned l)
{
    unsigned pow = 10;
    while(l >= pow)
        pow *= 10
    return h * pow + l;        
