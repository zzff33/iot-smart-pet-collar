#include "max30102_read.h"
#include "max30102.h"
#include "algorithm.h"
#include "myiic.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"

#define MAX_BRIGHTNESS 255

uint32_t aun_ir_buffer[500]; 		//IR LED sensor data
int32_t n_ir_buffer_length = 500;   //data length
uint32_t aun_red_buffer[500];    	//Red LED sensor data
int32_t n_sp02; 		//SPO2 value
int8_t ch_spo2_valid;   //indicator to show if the SP02 calculation is valid
int32_t n_heart_rate;   //heart rate value
int8_t  ch_hr_valid;    //indicator to show if the heart rate calculation is valid
uint8_t uch_dummy;

extern uint8_t dis_hr;
extern uint8_t dis_spo2;

void ReadHeartRateSpO2(void)
{
	static uint8_t cnt=0;
	static uint8_t init_flag = 0;
	int i;
	uint16_t time_out;
	u8 temp[6];

	cnt++;
	if(cnt <= 15)
	{
		return;
	}
	cnt = 0;
	
	if(MAX30102_INT == 1)
	{
		return;
	}

	if(init_flag == 0)
	{
		init_flag = 1;
		for(i=0;i<n_ir_buffer_length;i++)
		{
			while(MAX30102_INT==1)
			{
				time_out++;
				if(time_out >= 100)
				{
					time_out = 0;
					return;
				}
				delay_us(100);
			}
			max30102_FIFO_ReadBytes(REG_FIFO_DATA,temp);
			aun_red_buffer[i] =  (long)((long)((long)temp[0]&0x03)<<16) | (long)temp[1]<<8 | (long)temp[2];    // Combine values to get the actual number
			aun_ir_buffer[i] = (long)((long)((long)temp[3] & 0x03)<<16) |(long)temp[4]<<8 | (long)temp[5];   // Combine values to get the actual number
		}
		//calculate heart rate and SpO2 after first 500 samples (first 5 seconds of samples)
		maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid); 
	}
	
	for(i=0;i<450;i++)
	{
		aun_red_buffer[i]=aun_red_buffer[i+50];
		aun_ir_buffer[i]=aun_ir_buffer[i+50];
	}
	
	for(i=450;i<500;i++)
	{
		while(MAX30102_INT==1);
		max30102_FIFO_ReadBytes(REG_FIFO_DATA,temp);
		aun_red_buffer[i] =  (long)((long)((long)temp[0]&0x03)<<16) | (long)temp[1]<<8 | (long)temp[2];    // Combine values to get the actual number
		aun_ir_buffer[i] = (long)((long)((long)temp[3] & 0x03)<<16) |(long)temp[4]<<8 | (long)temp[5];   // Combine values to get the actual number
	}
	
	maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
	if(ch_hr_valid == 1 &&  n_heart_rate > 70 && n_heart_rate < 120 && ch_spo2_valid ==1 && n_sp02 > 70 && n_sp02 < 100)
	{
		dis_hr = n_heart_rate;
		dis_spo2 = n_sp02;
	}
}

