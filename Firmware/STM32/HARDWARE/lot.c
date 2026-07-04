#include "lot.h"
#include "usart.h"
#include "delay.h"
#include "string.h"


#define MAX_RUN_CNT 	3
#define MAX_WAIT_TIME 	3

#define LOT_EN_RCC		RCC_APB2Periph_GPIOA
#define LOT_EN_GPIO		GPIOA
#define LOT_EN_PINS		GPIO_Pin_8


#define Hostname  	"anszgfn.iot.gz.baidubce.com"
#define Client_Id  	"smart_pet_collar_device_15"
#define Username  	"thingidp@anszgfn|smart_pet_collar_device_15|0|MD5"
#define Password  	"d95bda79e19b27bdc64438088abff846"
#define Topic 	  	"$iot/smart_pet_collar_device_15/user/msg"


volatile uint8_t mqtt_status = 0; // 全局变量
uint8_t wifi_connect_state = 0;
uint8_t tcp_connect_state = 0;
char ip_addr[20];
char gateway_addr[20];

uint8_t lora_ack_msg[200];
uint8_t lora_ack_recv_finish = 0;

void lot_gpio_reset_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LOT_EN_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LOT_EN_PINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LOT_EN_GPIO, &GPIO_InitStructure);			
	GPIO_ResetBits(LOT_EN_GPIO,LOT_EN_PINS);
	delay_ms(1000);
	delay_ms(1000);
	GPIO_SetBits(LOT_EN_GPIO,LOT_EN_PINS);
}

void lot_init(void)
{
	char order[200];
	
	/* 复位模块 */
	lot_gpio_reset_init();
	
	/* 读SIM卡状态 */
	while(!lot_order_config("AT+CPIN?","+CPIN: READY",500))
	{
		delay_ms(100);
	}
	
	/* 查询网络状态 */
	while(!lot_order_config("AT+CEREG?","+CEREG: 0,1",500))
	{
		delay_ms(100);
	}
	
	/* 查询网络附着状态 */
	while(!lot_order_config("AT+CGATT?","+CGATT: 1",500))
	{
		delay_ms(100);
	}
	

	/* 配置客户端信息 */
	sprintf(order,"AT+MQTTCONN=0,\"%s\",1883,\"%s\",\"%s\",\"%s\"",Hostname,Client_Id,Username,Password);
	while(!lot_order_config(order,"+MQTTURC: \"conn\",0,0",1000))
	{
		delay_ms(50);
	}
	
	/* 配置客户端信息 */
	sprintf(order,"AT+MQTTSUB=0,\"%s\",0",Topic);
	while(!lot_order_config(order,"+MQTTSUB: 0",1000))
	{
		delay_ms(50);
	}
}


void lot_ack_check(uint8_t *buff,uint8_t len)
{
	lora_ack_recv_finish = 1;
	memcpy(lora_ack_msg,buff,len);
}

/* AT+MQTTPUB=0,"topic/t",0,0,0,5,"HELLO" */
void lot_send_data(char *data)
{
  char buff[200];
	mqtt_status = 1; // 标记函数被调用
	memset(buff,0,sizeof(buff));
	sprintf(buff,"AT+MQTTPUB=0,\"%s\",0,0,0,%d,\"%s\"",Topic,strlen(data),data);
	usart_send_buff((uint8_t *)buff,strlen(buff));
}

uint8_t lot_order_config(char *order,char *ack,uint32_t timeout)
{
	uint32_t delay = 0;
	uint8_t success_flag = 0;
	
	usart_send_buff((uint8_t *)order,strlen(order));
	while(1)
	{
		delay++;
		if(lora_ack_recv_finish)
		{
			lora_ack_recv_finish = 0;
			if(strstr((char *)lora_ack_msg,ack) != 0)
			{
				success_flag = 1;
				break;
			}
		}
		if(delay >= timeout)
		{
			break;
		}
		delay_ms(1);
	}
	
	return success_flag;
}

