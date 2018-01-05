#ifndef _BASE_H_
#define _BASE_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

/* Public typedef ------------------------------------------------------------*/
typedef struct
{
  uint8_t *packet;
  uint16_t length;
}ArrayStruct;

/* Public define -------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
ArrayStruct* Array_New(uint16_t length);
void Array_Free(ArrayStruct* array);
void Delay(uint16_t count);

#endif