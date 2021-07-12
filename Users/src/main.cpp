#include "main.h"

void main()
{
  int temp_int, temp_div;
  float Temp;
  
  union Union{
    float temperature_f;
    unsigned char temperature_ch [4];
  };
  
  Union change_temp;
  
  uint16_t data;
  Init_Clock();
  Init_Timer();
  Init_GPIO_LCD();
  Init_GPIO_DS18B20();
  Init_UART();
  
   while(1)
   {   
      Clear_LCD();
      data = getTempr();
      if(data > 0xF000){
        data = 0xFFFF - data + 1;
        Send_symbol_LCD('-');
      }
      Temp = (float)data*0.0625;
      temp_int = Temp;
      Send_symbol_LCD(temp_int/10+48);
      Send_symbol_LCD(temp_int%10+48);
      Send_symbol_LCD('.');
      temp_div= (Temp-temp_int)*100;
      Send_symbol_LCD(temp_div/10+48);
      Send_symbol_LCD(temp_div%10+48);
      
      delay(20000);
      change_temp.temperature_f = Temp;
      for(int i = 0; i <4; i++){
        USART_SendData(UART5, change_temp.temperature_ch[i]);
        delay(200);
      }
   }
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
while (1){}
}
#endif