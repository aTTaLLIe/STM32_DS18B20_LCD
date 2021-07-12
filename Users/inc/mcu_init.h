#ifndef MCU_INI_H
#define MCU_INI_H

#include "stm32f7xx.h"
#include "stm32f7xx_gpio.h"
#include "stm32f7xx_rcc.h"
#include "stm32f7xx_conf.h"
#include "stm32f7xx_tim.h"
#include "stm32f7xx_flash.h"
#include "stm32f7xx_usart.h"
#include "misc.h"
#include "math.h"

void delay(int);
void Init_Clock(void);
void Init_Timer(void);

#endif