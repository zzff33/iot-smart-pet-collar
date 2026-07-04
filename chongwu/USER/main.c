#include "delay.h"
#include "string.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "math.h"
#include "oled.h"
#include "beep.h"
#include "adc.h"
#include "ADXL345.h"
#include "ds18b20.h"
#include "gps.h"
#include "lot.h"
#include "max30102.h"
#include "max30102_read.h"


uint8_t dis_hr=0,hr_thre = 130;		//心率 心率阈值
uint8_t dis_spo2=0,spo2_thre = 90; 	//血氧 血氧阈值
uint32_t step_num = 0;				//步数
float temp,temp_thre = 40;			//体温 体温阈值
uint8_t alarm_en;					//报警使能状态位


void get_health_para(void);
void sys_state_report(void);
void sys_state_diplay(void);
void beep_alarm_ctrl(void);
void check_step_cnt(void);


int main(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为 115200
	uart2_init(9600);		//接收GPS数据
	OLED_Init();
	BEEP_Init();
	ADXL345_init();	//初始化加速度传感器
	DS18B20_Init();
	MAX30102_Init();		//初始化心率血氧传感器
	OLED_ShowString(0,0,(uint8_t *)"Network connect...",12,1);
	OLED_Refresh();
	lot_init();
	while(1)
	{
		/* 获取温度 */
		temp = DS18B20_Get_Temp();
		
		/* 解析经纬度信息 */
		parse_gps_msg();
		
		/* 计步 */
		check_step_cnt();
		
		/* 获取心率血氧 */
		ReadHeartRateSpO2();
		
		/* 蜂鸣器报警 */
		beep_alarm_ctrl();
		
		/* 上报系统状态 */
		sys_state_report();
		
		/* 屏幕显示系统状态 */
		sys_state_diplay();
		
		// 在 while(1) 内部，例如在 sys_state_display() 之后

		
		delay_ms(50);
		// 在 while(1) 内部，例如在 sys_state_display() 之后


	}
}


void sys_state_diplay(void)
{
	uint8_t txt[20];
	
	OLED_Clear();

	/* 体温 */
	OLED_ShowChinese(0,0,0,16,1);OLED_ShowChinese(16,0,1,16,1);
	sprintf((char *)txt,":%.1f'C	",temp);
	OLED_ShowString(32,0,txt,16,1);

	/* 心率 */
	OLED_ShowChinese(0,16,16,16,1);OLED_ShowChinese(16,16,17,16,1);
	sprintf((char *)txt,":%d   ",dis_hr);
	OLED_ShowString(32,16,txt,16,1);
	
	/* 血氧 */
	OLED_ShowChinese(0,32,18,16,1);OLED_ShowChinese(16,32,19,16,1);
	sprintf((char *)txt,":%d   ",dis_spo2);
	OLED_ShowString(32,32,txt,16,1);
	
	/* 步数 */
	OLED_ShowChinese(0,48,2,16,1);OLED_ShowChinese(16,48,3,16,1);
	sprintf((char *)txt,":%d    ",step_num);
	OLED_ShowString(32,48,txt,16,1);
	
	OLED_Refresh();
}

/* 上报系统状态 */
void sys_state_report(void)
{
	static uint8_t cnt = 0;
	char buff[100];
	
	cnt++;
	if(cnt > 15)
	{
		cnt = 0;
		
		sprintf(buff,"{1,%.1f,%.0f,%d,%d,%d,%d,%d,%f,%f}",temp,temp_thre,step_num,dis_hr,hr_thre,dis_spo2,spo2_thre,longitude,latitude);
		lot_send_data(buff);
	}
}

/* 检测是否运动，计步 */
void check_step_cnt(void)
{
	float ang_x,ang_y,ang_z; 
	static short flag,cnt,cnt1;

	/* 读加速度传感器的三轴角度 */
	Get_Gngle(&ang_x,&ang_y,&ang_z);
	
	if(fabs(ang_y) <= 20)
		flag = 1;
	
	if(flag == 1 && fabs(ang_y) >= 50)
	{
		flag = 0;
		step_num++;
	}
}

/* 接收APP下发的指令 */
void app_data_analyze(uint8_t *buff)
{
	char data_str[100];
	int data_len,data_len1,cmd_type;
	int data;

	// 找到 "+MQTTURC: "publish"" 的位置
    char *bytes_pos = strstr((char *)buff, "+MQTTURC: \"publish\"");
    if (bytes_pos == NULL) {
        return;
    }
	
	/* 校验数据 */
	if(sscanf(bytes_pos,"%*[^,],%*[^,],%*[^,],%*[^,],%d,%d,%s",&data_len,&data_len1,data_str) != 3)
		return;
	
	if(sscanf(data_str,"{2,%d,%d}",&cmd_type,&data) == 2)
	{
		switch(cmd_type)
		{
			/* 开启报警 */
			case 0x01:
			{
				alarm_en = data;
				break;
			}
			/* 清除步数 */
			case 0x02:
			{
				step_num = 0;
				break;
			}
			/* 设置体温阈值 */
			case 0x03:
			{
				temp_thre = data;
				break;
			}
			/* 设置心率阈值 */
			case 0x04:
			{
				hr_thre = data;
				break;
			}
			/* 设置血氧阈值 */
			case 0x05:
			{
				spo2_thre = data;
				break;
			}
		}
	}
}

/* 蜂鸣器 语音报警 */
void beep_alarm_ctrl(void)
{
	static uint8_t cnt1 = 0;
	
	/* 丢失报警 */
	if(alarm_en)
	{
		cnt1++;
		if(cnt1 >= 20)
			cnt1 = 0;
		BEEP_Ctrl = cnt1 > 10?1:0;
	}
	/* 体温异常报警 */
	else if(temp > temp_thre)
	{
		cnt1++;
		if(cnt1 >= 20)
			cnt1 = 0;
		BEEP_Ctrl = cnt1 > 10?1:0;
	}
	/* 心率异常报警 */
	else if(dis_hr > hr_thre)
	{
		cnt1++;
		if(cnt1 >= 20)
			cnt1 = 0;
		BEEP_Ctrl = cnt1 > 10?1:0;
	}
	/* 血氧异常报警 */
	else if(dis_spo2 != 0 && dis_spo2 < spo2_thre)
	{
		cnt1++;
		if(cnt1 >= 20)
			cnt1 = 0;
		BEEP_Ctrl = cnt1 > 10?1:0;
	}
	else
	{
		BEEP_Ctrl = 0;
	}
}
