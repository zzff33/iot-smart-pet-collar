#ifndef __IIC_H
#define __IIC_H
 
#include "sys.h"	
 
void Set_IIC_SDA_OUT(void);
void Set_IIC_SDA_IN(void);
void IIC_init(void);
void IIC_start(void);
void IIC_stop(void);
void IIC_ack(void);
void IIC_noack(void);
uint8_t IIC_wait_ack(void);
void IIC_send_byte(uint8_t txd);
uint8_t IIC_read_byte(uint8_t ack);


#endif

