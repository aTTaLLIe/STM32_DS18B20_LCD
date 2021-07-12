#ifndef LCD_H
#define LCD_H

#include "mcu_init.h"

void Init_LCD(void);
void Clear_LCD(void);
void Send_symbol_LCD(char);
void Init_GPIO_LCD(void);

#endif