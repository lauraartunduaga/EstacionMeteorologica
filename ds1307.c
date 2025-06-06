#include "DS1307.h"
#include "I2C.h"
#define _XTAL_FREQ 8000000
// I2C por hardware




// BCD helpers
uint24_t bin2bcd(uint24_t val) {
    return ((val / 10) << 4) | (val % 10);
}

uint24_t bcd2bin(uint24_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

// RTC
void DS1307_Init() {
    uint24_t sec;

    I2C_Master_Start();
    I2C_Master_Write(DS1307_ADDRESS_WRITE);
    I2C_Master_Write(0x00);
    I2C_Master_RepeatedStart();
    I2C_Master_Write(DS1307_ADDRESS_READ);
    sec = I2C_Master_Read(0);
    I2C_Master_Stop();

    sec &= 0x7F; // Clear CH bit

    I2C_Master_Start();
    I2C_Master_Write(DS1307_ADDRESS_WRITE);
    I2C_Master_Write(0x00);
    I2C_Master_Write(bin2bcd(sec));
    I2C_Master_Stop();
}

void DS1307_SetDateTime(uint24_t day, uint24_t month, uint24_t year, uint24_t dow, uint24_t hour, uint24_t min, uint24_t sec) {
    I2C_Master_Start();
    I2C_Master_Write(DS1307_ADDRESS_WRITE);
    I2C_Master_Write(0x00);
    I2C_Master_Write(bin2bcd(sec));
    I2C_Master_Write(bin2bcd(min));
    I2C_Master_Write(bin2bcd(hour));
    I2C_Master_Write(bin2bcd(dow));
    I2C_Master_Write(bin2bcd(day));
    I2C_Master_Write(bin2bcd(month));
    I2C_Master_Write(bin2bcd(year));
    I2C_Master_Stop();
}

void DS1307_GetDateTime(uint24_t *day, uint24_t *month, uint24_t *year, uint24_t *dow, uint24_t *hour, uint24_t *min, uint24_t *sec) {
    I2C_Master_Start();
    I2C_Master_Write(DS1307_ADDRESS_WRITE);
    I2C_Master_Write(0x00);
    I2C_Master_RepeatedStart();
    I2C_Master_Write(DS1307_ADDRESS_READ);
    *sec  = bcd2bin(I2C_Master_Read(1));
    *min  = bcd2bin(I2C_Master_Read(1));
    *hour = bcd2bin(I2C_Master_Read(1));
    *dow  = bcd2bin(I2C_Master_Read(1));
    *day  = bcd2bin(I2C_Master_Read(1));
    *month= bcd2bin(I2C_Master_Read(1));
    *year = bcd2bin(I2C_Master_Read(0));
    I2C_Master_Stop();
}
