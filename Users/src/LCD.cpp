#include "mcu_init.h"

GPIO_InitTypeDef GPIO_Struct_C, GPIO_Struct_D;

//************************LCD*************************************
void Init_LCD(void){
    GPIO_Write(GPIOD, 0b0000000000001100); // Enable LCD
    GPIO_ToggleBits(GPIOC, GPIO_Pin_10);
    delay(20000);
    GPIO_ToggleBits(GPIOC, GPIO_Pin_10);
    delay(20000);
    GPIO_Write(GPIOD, 0b0000000000000001); // Clear LCD
    GPIO_ToggleBits(GPIOC, GPIO_Pin_10);
    delay(20000);

    GPIO_ResetBits(GPIOC, GPIO_Pin_8); 
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    GPIO_ResetBits(GPIOC, GPIO_Pin_10);
}

void Init_GPIO_LCD(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//******************************************************         
    GPIO_Struct_D.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Struct_D.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Struct_D.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
    GPIO_Struct_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Struct_D.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOD, &GPIO_Struct_D);
    
    GPIO_Struct_C.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Struct_C.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Struct_C.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10; // 8- RS, 9- R/W, 10- E
    GPIO_Struct_C.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Struct_C.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_Struct_C);    
//*******************************************************  

    GPIO_ResetBits(GPIOC, GPIO_Pin_8); 
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    GPIO_ResetBits(GPIOC, GPIO_Pin_10);
    
    Init_LCD();
}


void Clear_LCD(void){
    GPIO_Write(GPIOD, 0b0000000000000010); // Clear LCD
    GPIO_ToggleBits(GPIOC, GPIO_Pin_10);
    delay(20000);

    GPIO_ResetBits(GPIOC, GPIO_Pin_8); 
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    GPIO_ResetBits(GPIOC, GPIO_Pin_10);
}

void Send_symbol_LCD(char symbol){
   int send_sym = (int)symbol;
   delay(2000);
     GPIO_Write(GPIOD, send_sym); // Send symbol
     GPIO_SetBits(GPIOC, GPIO_Pin_8);
     GPIO_ToggleBits(GPIOC, GPIO_Pin_10);
   delay(2000);
     GPIO_ToggleBits(GPIOC, GPIO_Pin_10);
   delay(2000);
     GPIO_ResetBits(GPIOC, GPIO_Pin_8); 
     GPIO_ResetBits(GPIOC, GPIO_Pin_9);
     GPIO_ResetBits(GPIOC, GPIO_Pin_10);
  }