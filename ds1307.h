#include <xc.h> 

#define _XTAL_FREQ 8000000

#define DS1307_ADDRESS_WRITE 0xD0
#define DS1307_ADDRESS_READ  0xD1

// Prototipos

void DS1307_Init();
void DS1307_SetDateTime(uint24_t day, uint24_t month, uint24_t year, uint24_t dow, uint24_t hour, uint24_t min, uint24_t sec);
void DS1307_GetDateTime(uint24_t *day, uint24_t *month, uint24_t *year, uint24_t *dow, uint24_t *hour, uint24_t *min, uint24_t *sec)
