#ifndef __LOT_H
#define __LOT_H	 
#include "sys.h"



void lot_init(void);//≥ı ºªØ
void lot_ack_check(uint8_t *buff,uint8_t len);
uint8_t lot_order_config(char *order,char *ack,uint32_t timeout);
void lot_send_data(char *data);


#endif
