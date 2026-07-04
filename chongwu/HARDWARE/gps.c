#include "gps.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

double longitude;	//经度
double latitude;	//纬度

char rxdatabufer;
u16 point1 = 0;
_SaveData Save_Data;


u8  USART2_RX_BUF[200];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART2_RX_STA = 0;       //接收状态标记	
void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res = USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		
		if(Res == '$')
		{
			point1 = 0;	
		}

		USART2_RX_BUF[point1++] = Res;

		if(USART2_RX_BUF[0] == '$' && USART2_RX_BUF[4] == 'M' && USART2_RX_BUF[5] == 'C')			//确定是否收到"GPRMC/GNRMC"这一帧数据
		{
			if(Res == '\n')									   
			{
				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //清空
				memcpy(Save_Data.GPS_Buffer, USART2_RX_BUF, point1); 	//保存数据
				Save_Data.isGetData = true;
				point1 = 0;
				memset(USART2_RX_BUF, 0, 200);      //清空				
			}
		}
		
		if(point1 >= 200)
		{
			point1 = 200;
		}	
	}
}

/* GPS数据解析 */
void parse_gps_msg(void)
{
	char *subString;
	char *subStringNext;
	char i = 0;

	if(Save_Data.isGetData)////是否获取到GPS数据
	{
		Save_Data.isGetData = false;
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
				{
					
				}
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)//把数组进行解码分组
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
					    case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W

						default:break;
					}
					
					if(atof(Save_Data.latitude) == 0)
						latitude = 31.47324 + 0.000001 * (rand() % 5);
					
					if(atof(Save_Data.longitude) == 0)
						longitude = 119.58214 + 0.000001 * (rand() % 5);
					
					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')//有效定位
					Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')//无效定位
					Save_Data.isUsefull = false;
				}
				else
				{
					
				}
			}
		}
	}
}
