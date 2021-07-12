#include "mcu_init.h"
#include "DS18B20.h"

GPIO_InitTypeDef GPIO_Struct_B, GPIO_Struct_B11;
int bit=0;

void Init_GPIO_DS18B20(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//******************************************************             
    GPIO_Struct_B.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Struct_B.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Struct_B.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_11 | GPIO_Pin_0;
    GPIO_Struct_B.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Struct_B.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOB, &GPIO_Struct_B);
//*******************************************************   
    Init_DS18B20();
}

void GPIOOUT(void){
        GPIO_Struct_B11.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_Struct_B11.GPIO_Speed = GPIO_Fast_Speed;
        GPIO_Struct_B11.GPIO_Pin = GPIO_Pin_11;
        GPIO_Struct_B11.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Struct_B11.GPIO_OType = GPIO_OType_OD;
        GPIO_Init(GPIOB, &GPIO_Struct_B11);
}
void GPIOIN(void){      
        GPIO_Struct_B11.GPIO_Mode = GPIO_Mode_IN;
        GPIO_Struct_B11.GPIO_Speed = GPIO_Fast_Speed;
        GPIO_Struct_B11.GPIO_Pin = GPIO_Pin_11;
        GPIO_Struct_B11.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Struct_B11.GPIO_OType = GPIO_OType_OD;
        GPIO_Init(GPIOB, &GPIO_Struct_B11);
}

void Init_DS18B20(void){
  
    GPIOOUT();
    GPIO_ResetBits(GPIOB, GPIO_Pin_11);
    delay(250);//>480mks
    GPIOIN();
    delay(40);//>60mks
    bit = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    if(bit == 0){
      GPIO_SetBits(GPIOB, GPIO_Pin_0);
      delay(50000);
      GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    }
}

void one_wire_write_bit(uint8_t bitout)
{
       GPIOOUT();
       GPIO_ResetBits(GPIOB, GPIO_Pin_11);
       if(bitout==1)
       {
         delay(2);//10mks
         GPIOIN();
         delay(30);//100mks
       }
       else
       {
         delay(31);//70mks
         GPIOIN();
         delay(10);//50mks
       }
}

uint8_t one_wire_read_bit(void)
{
	uint8_t bits = 0;
        GPIOOUT();
        GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	delay(2);
	GPIOIN();
        delay(7);
	bits = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	delay(30);
	return bits;
}

void one_wire_write_byte(uint8_t data)
{
	for(uint8_t i = 0; i<8; i++) 
        {
        one_wire_write_bit(data>>i & 1);
        }
}

uint16_t getTempr(void)
{
        int data;
        Init_DS18B20();
	one_wire_write_byte(0xCC);
	one_wire_write_byte(0x44);
        delay(400000);  
	Init_DS18B20();
	one_wire_write_byte(0xCC);
	one_wire_write_byte(0xBE);
//        one_wire_write_byte(0x33);
	for(uint8_t i = 0; i<16; i++) 
        {
          data += (uint16_t)one_wire_read_bit()<<i;
          delay(1);
        }
	return data;
}