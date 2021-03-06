#ifndef _STM32_UARTDMA_H_
#define _STM32_UARTDMA_H_

/* Includes ------------------------------------------------------------------*/
#include "../Sys_Conf.h"
#include "BufferQueue.h"

/* Public typedef ------------------------------------------------------------*/

typedef struct
{
  DMA_HandleTypeDef *rxDma;
  UART_HandleTypeDef *uart;
  RxBufferStruct rxBuffer;
  RxQueueStruct rxQueue;
  uint16_t bufferLength;
  uint16_t start;
  uint16_t end;
}UartRxDmaStruct;

/* Public define -------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
void Stm32_UartRxDma_Init(UartRxDmaStruct *uartDma, DMA_HandleTypeDef *rxDma, UART_HandleTypeDef *uart);
void Stm32_UartRxDma_IntHandle(UartRxDmaStruct *uartDma);  
#endif