#ifndef _SIMPLE_BUFFER_H_
#define _SIMPLE_BUFFER_H_

/* Includes ------------------------------------------------------------------*/
#include "../Sys_Conf.h"
#include "BufferQueue_Conf.h"

/* Public define -------------------------------------------------------------*/

#define RX_FLAG_USED    (1<<0)          // 被占用

#define TX_FLAG_USED    (1<<0)          // 被占用
#define TX_FLAG_SENDED  (1<<1)          // 已发送
#define TX_FLAG_RT      (1<<2)          // 需要进行重新发送
#define TX_FLAG_TIMEOUT (1<<3)          // 是否超时标志位
#define TX_FLAG_MC      (1<<7)          // 手动清除


/* Public typedef ------------------------------------------------------------*/
typedef enum
{
  TX_ONCE_AC = 0,                               // 发一次，自动清除
  TX_ONCE_MC = TX_FLAG_MC,                      // 发一次，手动清除
  TX_MULTI_AC = TX_FLAG_RT,                     // 发多次，自动清除，重发次数在TxQueueStruct.maxCount
  TX_MULTI_MC = TX_FLAG_RT | TX_FLAG_MC,        // 发多次，手动清除
}TxModeEnum;

typedef struct
{
  uint8_t buffer[BUFFER_LENGTH];
  uint16_t count;
}RxBufferStruct;       //接收缓冲，包含N字节的缓冲池以及计数器

//*************************基础块单位*******************
typedef struct
{
  uint8_t flag;
  uint8_t *message;
  uint16_t length;
}RxBaseBlockStruct;        //接收块

typedef struct
{
  uint8_t *message;
  uint16_t length;
  uint16_t flag;
  uint16_t retransCounter;
  TX_ID_SIZE id;
#ifdef TX_BLOCK_TIMEOUT
    uint32_t time;
#endif
}TxBaseBlockStruct;        // 发送块     

//***********************高级块缓冲单位************************
typedef struct
{
  uint32_t time;                                // 对不同的发送函数来说，有着不同的发送间隔，需要进行单独设置
  uint16_t usedBlockQuantity;                   // 已使用的块数量
  uint16_t maxTxCount;                          // 最大重发次数
  uint16_t interval;                            // 发送间隔
  uint16_t indexCache;                          // 索引缓存，配合无序发送使用
  BoolEnum isTxUnordered;                       // 是否无序发送
  TxBaseBlockStruct txBlocks[BLOCK_COUNT];
}TxQueueStruct;             // 发送块缓冲队列

typedef struct
{
  uint32_t time; 
  uint16_t usedBlockQuantity;
  RxBaseBlockStruct rxBlocks[BLOCK_COUNT];
}RxQueueStruct;             //接收块缓冲队列

//*********************错误枚举**************************
typedef enum
{
  TxBlockError_TimeOut = 0
}TxBlockError;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/

/* 接收需要的函数 */
void ReceiveSingleByte(uint8_t rxByte, RxBufferStruct *rxBuffer);                                                       //接收单字节数据，填充至缓冲中
uint16_t RxQueue_Add(RxQueueStruct *rxQueue, uint8_t *packet, uint16_t Len);                                            //将接收缓冲中的数据填充到接收报文队列中
void RxQueue_Handle(RxQueueStruct *rxQueue, void (*RxPacketHandle)(uint8_t*, uint16_t, void *), void *para);            //接收报文队列处理

/* 发送需要的函数 */
uint16_t TxQueue_Add(TxQueueStruct *txQueue, uint8_t *message, uint16_t length, TxModeEnum mode);                       //填充发送队列，包含清除重发以及未使用标志位为1
uint16_t TxQueue_AddWithId(TxQueueStruct *txQueue, uint8_t *message, uint16_t length, TxModeEnum mode, TX_ID_SIZE id);
void TxQueue_Handle(TxQueueStruct *txQueue, BoolEnum (*Transmit)(uint8_t*, uint16_t));                                      //发送报文队列处理

void TxQueue_FreeByFunc(TxQueueStruct *txQueue, BoolEnum (*func)(uint8_t*, uint16_t, void*), void *para);               //通过指定函数，释放指定发送块
void TxQueue_FreeById(TxQueueStruct *txQueue,  TX_ID_SIZE id);                                                          //通过ID，释放指定发送块

#endif

