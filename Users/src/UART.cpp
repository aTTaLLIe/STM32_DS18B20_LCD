#include "mcu_init.h"

USART_InitTypeDef UART_Structure;
GPIO_InitTypeDef GPIO_UART_Structure;

//************************UART*************************************
void Init_UART(void){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);   
    
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8 , GPIO_AF7_UART5);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9 , GPIO_AF7_UART5);
  
    GPIO_UART_Structure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_UART_Structure.GPIO_OType = GPIO_OType_PP;
    GPIO_UART_Structure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_UART_Structure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_UART_Structure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOB, &GPIO_UART_Structure);
    
    UART_Structure.USART_BaudRate = 115200;
    UART_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART_Structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    UART_Structure.USART_Parity = USART_Parity_No;
    UART_Structure.USART_StopBits = USART_StopBits_1;
    UART_Structure.USART_WordLength = USART_WordLength_8b;
    USART_Init(UART5, &UART_Structure);
    
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);
  
    NVIC_EnableIRQ(UART5_IRQn);
    NVIC_SetPriority(UART5_IRQn, 0);
}


extern "C" void UART5_IRQHandler(){
  if(USART_GetITStatus(UART5, USART_IT_RXNE)){
    USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    char Element = USART_ReceiveData(UART5);
  }
}