#include "mcu_init.h"

TIM_TimeBaseInitTypeDef Timer_Struct;
NVIC_InitTypeDef NVIC_InitStructure;

int count = 0;

void delay(int mksec){
  TIM_Cmd(TIM3, ENABLE);
  count = 0;
  while(1){
     if(count >= mksec){
         count = 0;
         TIM_Cmd(TIM3, DISABLE);
         break;
     }
  }
}


void Init_Clock(void){
    RCC_DeInit();
    RCC_HSICmd(DISABLE);
    RCC_HSEConfig(RCC_HSE_ON);
    RCC_WaitForHSEStartUp();
    
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PLLConfig(RCC_PLLSource_HSE, 4, 192, 2, 7);
    RCC_PLLCmd(ENABLE);
    
    FLASH_SetLatency(FLASH_Latency_4);
    FLASH_PrefetchBufferCmd(ENABLE);
    
    while(RCC_GetFlagStatus( RCC_FLAG_PLLRDY) == RESET);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource()!=0x08);

    SystemCoreClockUpdate();
}

void Init_Timer(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
//******************************************************         
    TIM_TimeBaseStructInit(&Timer_Struct);
    Timer_Struct.TIM_Prescaler = 192-1;//80
    Timer_Struct.TIM_Period = 1;// 2 mks   1
    Timer_Struct.TIM_CounterMode = TIM_CounterMode_Up; 
    Timer_Struct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &Timer_Struct);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

extern "C" void TIM3_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
    count++;
 }
}