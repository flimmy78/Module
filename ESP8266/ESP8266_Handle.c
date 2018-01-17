/* Includes ------------------------------------------------------------------*/
#include "string.h"

#include "stm32f0xx_hal.h"
#include "../UartDma/SimpleBuffer.h"
#include "ESP8266.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart2;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*********************************************************************************************

  * @brief  向ESP8266发送数据
  * @param  data：需要发送的数据指针
  * @param  length：数据长度  
  * @retval 无
  * @remark 

  ********************************************************************************************/
void ESP8266_SendData(uint8_t *data, uint16_t length)
{
  HAL_UART_Transmit(&huart2, data, length, 1000);   //发送数据
}
/*********************************************************************************************

  * @brief  向ESP8266发送字符串
  * @param  string
  * @retval 无
  * @remark 

  ********************************************************************************************/
void ESP8266_SendString(const char *string)
{
  HAL_UART_Transmit(&huart2, (uint8_t*)string, strlen(string), 1000);   //发送数据
}
/*********************************************************************************************

  * @brief  模块硬件复位
  * @return 无
  * @remark 

  ********************************************************************************************/
void ESP8266_HardWareReset()
{
  
}
