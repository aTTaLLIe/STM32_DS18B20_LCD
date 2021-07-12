#ifndef DS18B20_H
#define DS18B20_H

#include "mcu_init.h"

void Init_DS18B20(void);
void one_wire_write_bit(uint8_t);
uint8_t one_wire_read_bit(void);
void one_wire_write_byte(uint8_t);
uint16_t getTempr(void);
void Init_GPIO_DS18B20(void);

#endif